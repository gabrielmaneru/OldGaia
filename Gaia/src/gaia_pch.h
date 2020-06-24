#pragma once
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <map>
#include <set>

#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <core/definitions.h>
#include <core/type_info.h>
#include <debug/log_manager.h>
#include <scene/serialize_functions.h>

