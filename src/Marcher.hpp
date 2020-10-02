#pragma once

#include <list>

#include "Vector.hpp"
#include "Objects.hpp"

class Marcher
{
public:
    Marcher(double h, double w, double x, double y, double z)
        : _ro(x, y, z)
        , _tl( h, -w, 1)
        , _tr( h,  w, 1)
        , _br(-h,  w, 1)
        , _bl(-h, -w, 1)
    { }

    Marcher(double h, double w, Vector3 ro)
        : _ro(ro)
        , _tl( h, -w, 1)
        , _tr( h,  w, 1)
        , _br(-h,  w, 1)
        , _bl(-h, -w, 1)
    { }

    void SetFrustrum(double h, double w)
    {
        _tl.SetXYZ( h, -w, 1);
        _tr.SetXYZ( h,  w, 1);
        _br.SetXYZ(-h,  w, 1);
        _bl.SetXYZ(-h, -w, 1);
    }

    void Offset(double x, double y, double z)
    {
        Vector3 tempVec(x, y, z);
        _ro += tempVec;
    }

    virtual ~Marcher()
    {
        /* std::list<BaseObject *>::iterator it;
        for (it = _objects.begin(); it != _objects.end(); ++it)
        {
            delete &it;
        } */
    }

    struct MarcherSettings
    {
        double minDist = 0.001;
        int stepMax = 1000;
    };
    MarcherSettings marcherSettings;

    void SetSettings(MarcherSettings newSet)
    {
        marcherSettings = newSet;
    }

    void SetSettings(double newMinDist, int newStepMax)
    {
        MarcherSettings newSet;
        newSet.minDist = newMinDist;
        newSet.stepMax = newStepMax;
        marcherSettings = newSet;
    }

    MarcherSettings GetSettings()
    {
        return marcherSettings;
    }

    double GetMinDE(Vector3 p)
    {
        float modFactor = 1;
        Vector3 p_mod = p % modFactor;

        double min = 1000000000;

        for (const BaseObject *bo : _objects)
        {
            double d = bo->DE(p_mod);
            if (d < min)
                min = d;
        }

        return min;
    }

    typedef struct MarchOutput
    {
        int steps;
        double dist;
        Vector3 endPos;
        bool hit = false;
    } MarchOutput;

    MarchOutput March(Vector3 rd)
    {
        MarchOutput res;

        int steps = 0;
        double dist = 0;
        Vector3 p = _ro + rd * dist;

        while (steps < marcherSettings.stepMax)
        {
            float d = GetMinDE(p);
            if (d < marcherSettings.minDist)
            {
                res.hit = true;
                break;
            }

            dist += d;
            p = _ro + rd * dist;

            steps++;
        }

        res.steps = steps;
        res.dist = dist;
        res.endPos = p;

        return res;
    }

    void AddObject(BaseObject* newObj)
    {
        _objects.emplace_back(newObj);
    }

    Vector3 NormToVec(double x, double y)
    {
        Vector3 top = Vector3::Lerp(_tl, _tr, x);
        Vector3 bot = Vector3::Lerp(_bl, _br, x);
        return Vector3::Lerp(top, bot, y).normalized();
    }

private:
    Vector3 _ro;

    Vector3 _tl;
    Vector3 _tr;
    Vector3 _br;
    Vector3 _bl;

    std::list<BaseObject *> _objects;
};
