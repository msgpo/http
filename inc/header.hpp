// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015-2016 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <cctype>
#include <vector>
#include <cstring>
#include <utility>
#include <ostream>
#include <algorithm>
#include <type_traits>

#include "span.hpp"
#include "common.hpp"

namespace http {

//-----------------------------------------------
// This class is used to store header information
// associated with an http message
//
// By default it is limited to 100 fields
// but the amount can be specified by using the
// appropriate constructor and provided method.
//-----------------------------------------------
class Header {
private:
  //-----------------------------------------------
  // Internal class type aliases
  //-----------------------------------------------
  using Map_Type       = std::pair<span, span>;
  using Field_Map      = std::vector<Map_Type>;
  using Const_Iterator = Field_Map::const_iterator;
  //-----------------------------------------------
public:
  //-----------------------------------------------
  // Default constructor that limits the amount
  // of fields that can be added to 100
  //-----------------------------------------------
  explicit Header();

  //-----------------------------------------------
  // Constructor to specify the limit of how many
  // fields that can be added
  //
  // @param limit - Capacity of how many fields can
  //                be added
  //-----------------------------------------------
  explicit Header(const Limit limit) noexcept;

  //-----------------------------------------------
  // Default destructor
  //-----------------------------------------------
  ~Header() noexcept = default;

  //-----------------------------------------------
  // Default copy constructor
  //-----------------------------------------------
  Header(const Header&) = default;

  //-----------------------------------------------
  // Default move constructor
  //-----------------------------------------------
  Header(Header&&) noexcept = default;

  //-----------------------------------------------
  // Default assignment operator
  //-----------------------------------------------
  Header& operator = (const Header&) = default;

  //-----------------------------------------------
  // Default move assignemt operator
  //-----------------------------------------------
  Header& operator = (Header&&) = default;

  //-----------------------------------------------
  // Add a new field to the current set
  //
  // @param field - The field name
  // @param value - The field value
  //
  // @return - true if the field was added, false
  //           otherwise
  //-----------------------------------------------
  bool add_field(const span& field, const span& value);

  //-----------------------------------------------
  // Change the value of the specified field
  //
  // If the field is absent from the set it will
  // be added with the associated value once its
  // within capacity
  //
  // @param field - The field name
  // @param value - The field value
  //
  // @return - true if successful, false otherwise
  //-----------------------------------------------
  bool set_field(const span& field, const span& value);

  //-----------------------------------------------
  // Check to see if the specified field is a
  // member of the set
  //
  // @param field - The field name
  //
  // @return - true if the field is a member,
  //           false otherwise
  //-----------------------------------------------
  bool has_field(const span& field) const noexcept;

  //-----------------------------------------------
  // Get the value associated with a field
  //
  // Should call <has_field> before calling this
  //
  // @param field - The field name
  //
  // @return - The value associated with the
  //           specified field name
  //-----------------------------------------------
  const span& get_value(const span& field) const noexcept;

  //-----------------------------------------------
  // Check to see if the set is empty
  //
  // @return - true if there are no fields within
  //           the set, false otherwise
  //-----------------------------------------------
  bool is_empty() const noexcept;

  //-----------------------------------------------
  // Check to see how many fields are currently
  // in the set
  //
  // @return - The amount of fields currently in
  //           the set
  //-----------------------------------------------
  Limit size() const noexcept;

  //-----------------------------------------------
  // Remove all fields from the set with the
  // specified name
  //
  // @param field - The field name to remove
  //-----------------------------------------------
  void erase(const span& field) noexcept;

  //-----------------------------------------------
  // Remove all fields from the set leaving it
  // empty
  //-----------------------------------------------
  void clear() noexcept;
private:
  //-----------------------------------------------
  // Class data members
  //-----------------------------------------------
  Field_Map map_;

  //-----------------------------------------------
  // Find the location of a field within the set
  //
  // @param field - The field name to locate
  //
  // @return - Iterator to the location of the field,
  //           else location to the end of the
  //           sequence
  //-----------------------------------------------
  Const_Iterator find(const span& field) const noexcept;

  //-----------------------------------------------
  // Operator to stream the contents of the set
  // into the specified output device
  //
  // The format is as follows:
  // field : value "\r\n"
  //-----------------------------------------------
  friend std::ostream& operator << (std::ostream&, const Header&);
}; //< class Header

} //< namespace http

#endif //< HTTP_HEADER_HPP
