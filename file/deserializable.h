/******************************************************************************
 * deserializable.h
 * Copyright 2011 Iain Peet
 *
 * Abstract base for classes which can retrieve their state from a JSON object.
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

#ifndef DESERIALIZABLE_H_
#define DESERIALIZABLE_H_

namespace Json { class Value; }

class Deserializable {
public:
    /* Read state from the given Json object.
     * @return true if read successfully, false if obj was invalid */
    virtual bool deserialize(const Json::Value &obj) = 0;
};

#endif //DESERIALIZABLE_H_
