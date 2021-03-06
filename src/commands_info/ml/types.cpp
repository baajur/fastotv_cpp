/*  Copyright (C) 2014-2020 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/ml/types.h>

#include <ostream>

namespace fastotv {
namespace commands_info {
namespace ml {

bool ImageBox::Equals(const ImageBox& box) const {
  return class_id == box.class_id && confidence == box.confidence && start == box.start && size == box.size;
}

std::ostream& operator<<(std::ostream& out, const ImageBox& box) {
  return out << "Class id: " << box.class_id << ", Confidence: " << box.confidence << ", Position: " << box.start
             << ", Size: " << box.size;
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv
