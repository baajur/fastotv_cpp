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

#include <fastotv/commands_info/catchup_undo_info.h>

#define ID_FIELD "id"

namespace fastotv {
namespace commands_info {

CatchupUndoInfo::CatchupUndoInfo() : sid_(invalid_stream_id) {}

CatchupUndoInfo::CatchupUndoInfo(const stream_id_t& sid) : sid_(sid) {}

CatchupUndoInfo::~CatchupUndoInfo() {}

bool CatchupUndoInfo::IsValid() const {
  return sid_ != invalid_stream_id;
}

void CatchupUndoInfo::SetStreamID(const stream_id_t& sid) {
  sid_ = sid;
}

stream_id_t CatchupUndoInfo::GetStreamID() const {
  return sid_;
}

bool CatchupUndoInfo::Equals(const CatchupUndoInfo& inf) const {
  return sid_ == inf.sid_;
}

common::Error CatchupUndoInfo::DoDeSerialize(json_object* serialized) {
  CatchupUndoInfo inf;
  json_object* jcid = nullptr;
  json_bool jcid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jcid);
  if (!jcid_exists) {
    return common::make_error_inval();
  }

  stream_id_t cid = json_object_get_string(jcid);
  if (cid == invalid_stream_id) {
    return common::make_error_inval();
  }
  inf.sid_ = cid;

  *this = inf;
  return common::Error();
}

common::Error CatchupUndoInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, ID_FIELD, json_object_new_string(sid_.c_str()));
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv
