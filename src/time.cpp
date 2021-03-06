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

#include <time.hpp>

namespace http {
namespace time {

///////////////////////////////////////////////////////////////////////////////
std::string from_time_t(const std::time_t time_) {
  auto tm = std::gmtime(&time_);

  if (tm) {
    std::ostringstream output;
    output << std::put_time(tm, "%a, %d %b %Y %H:%M:%S %Z");
    return output.str();
  }

  return std::string{};
}

///////////////////////////////////////////////////////////////////////////////
std::time_t to_time_t(const std::string& time_) {
  std::tm tm{};

  if (time_.empty()) goto error;

  // Format: Sun, 06 Nov 1994 08:49:37 GMT
  if (strptime(time_.c_str(), "%a, %d %b %Y %H:%M:%S %Z", &tm) not_eq nullptr) {
    return std::mktime(&tm);
  }

  // Format: Sunday, 06-Nov-94 08:49:37 GMT
  if (strptime(time_.c_str(), "%a, %d-%b-%y %H:%M:%S %Z", &tm) not_eq nullptr) {
    return std::mktime(&tm);
  }

  // Format: Sun Nov  6 08:49:37 1994
  if(strptime(time_.c_str(), "%a %b %d %H:%M:%S %Y", &tm) not_eq nullptr) {
    return std::mktime(&tm);
  }

  error:
  	return std::time_t{};
}

///////////////////////////////////////////////////////////////////////////////
std::string now() {
  auto time_object = std::time(nullptr);
  return from_time_t(time_object);
}

} //< namespace time
} //< namespace http
