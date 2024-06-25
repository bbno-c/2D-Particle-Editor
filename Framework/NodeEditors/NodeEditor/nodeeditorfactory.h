#pragma once

#include <QWidget>

#include "nodeeditor.h"

#include "nodeeditorlifetime.h"
#include "nodeeditoremitterrate.h"
#include "nodeeditorstarttransformation.h"
#include "nodeeditormaxparticles.h"
#include "nodeeditoremittershape.h"
#include "nodeeditorforcebytime.h"
#include "nodeeditorparticlespeed.h"
#include "nodeeditorrotationspeed.h"
#include "nodeeditorparticlesizebytime.h"
#include "nodeeditorparticlecolor.h"
#include "nodeeditortrailtype.h"

class NodeEditorFactory
{
public:
    NodeEditorFactory() = delete;
    static NodeEditor *create(int editorNodeid, QWidget *parent = nullptr)
    {
        switch (editorNodeid)
        {
            case 1:
                return new NodeEditorLifeTime(parent);
            case 2:
                return new NodeEditorEmitterRate(parent);
            case 3:
                return new NodeEditorStartTransformation(parent);
            case 4:
                return new NodeEditorMaxParticles(parent);
            case 5:
                return new NodeEditorEmitterShape(parent);
            case 6:
                return new NodeEditorForceByTime(parent);
            case 7:
                return new NodeEditorParticleSpeed(parent);
            case 8:
                return new NodeEditorRotationSpeed(parent);
            case 9:
                return new NodeEditorParticleSizeByTime(parent);
            case 10:
                return new NodeEditorParticleColor(parent);
            case 11:
                return new NodeEditorTrailType(parent);
            default:
                return nullptr;
        }
    }
};
