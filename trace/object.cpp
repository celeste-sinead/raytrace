/******************************************************************************
 * rayObject.cpp
 * Copyright 2010 Iain Peet
 *
 * Implements the base of some object in the ray graphics universe which
 * affects rays in some way.
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#include <math.h>
#include <json/value.h>

#include "object.h"

#include "util/trace.h"
#include "util/unit.h"
#include "lighting.h"
#include "ray.h"
#include "world.h"

static trc_ctl_t rayObjectTrc = {
    TRC_DFL_LVL,
    "RAY-OBJ",
    TRC_DFL_PRINT
};
#define TRACE(level, args...) \
    trc_printf(&rayObjectTrc,(level),1,args)

bool RayObject::deserialize(const Json::Value& obj) {

}

