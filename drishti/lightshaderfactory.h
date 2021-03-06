#ifndef LIGHTSHADERFACTORY_H
#define LIGHTSHADERFACTORY_H

#include "commonqtclasses.h"

#include <GL/glew.h>

class LightShaderFactory
{
 public :
  static QString getVal();

  static QString genOpacityShader(int, bool, bool);
  static QString genOpacityShaderRGB();

  static QString genAOLightShader();

  static QString genInitEmissiveShader();
  static QString genEmissiveShader();

  static QString genInitDLightShader();
  static QString genDLightShader();

  static QString genInitTubeLightShader();
  static QString genTubeLightShader();

  static QString genExpandLightShader();

  static QString genFinalLightShader();
  static QString genEFinalLightShader();

  static QString genInvertLightShader();

  static QString genDiffuseLightShader();

  static QString genMergeOpPruneShader();

  static QString blend(QString);
};

#endif
