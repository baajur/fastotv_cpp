/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/types/stream_link.h>

#define HTTP_FIELD "http_proxy"
#define HTTPS_FIELD "https_proxy"

namespace fastotv {

StreamLink::StreamLink() : http_proxy_(), https_proxy_() {}

StreamLink::StreamLink(const http_proxy_t& http, const http_proxy_t& https) : http_proxy_(http), https_proxy_(https) {}

bool StreamLink::IsValid() const {
  return true;
}

StreamLink::http_proxy_t StreamLink::GetHttp() const {
  return http_proxy_;
}

void StreamLink::SetHttp(const http_proxy_t& url) {
  http_proxy_ = url;
}

StreamLink::https_proxy_t StreamLink::GetHttps() const {
  return https_proxy_;
}

void StreamLink::SetHttps(const https_proxy_t& url) {
  https_proxy_ = url;
}

bool StreamLink::Equals(const StreamLink& url) const {
  return http_proxy_ == url.http_proxy_ && https_proxy_ == url.https_proxy_;
}

common::Optional<StreamLink> StreamLink::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<StreamLink>();
  }

  StreamLink res;
  common::Value* http_field = json->Find(HTTP_FIELD);
  std::string url_str;
  if (http_field && http_field->GetAsBasicString(&url_str)) {
    res.http_proxy_ = http_proxy_t(url_str);
  }

  common::Value* https_field = json->Find(HTTPS_FIELD);
  if (https_field && https_field->GetAsBasicString(&url_str)) {
    res.https_proxy_ = https_proxy_t(url_str);
  }
  return res;
}

common::Error StreamLink::DoDeSerialize(json_object* serialized) {
  StreamLink res;
  json_object* jhttp = nullptr;
  json_bool jhttp_exists = json_object_object_get_ex(serialized, HTTP_FIELD, &jhttp);
  if (jhttp_exists) {
    res.SetHttp(http_proxy_t(json_object_get_string(jhttp)));
  }

  json_object* jhttps = nullptr;
  json_bool jhttps_exists = json_object_object_get_ex(serialized, HTTPS_FIELD, &jhttps);
  if (jhttps_exists) {
    res.SetHttps(https_proxy_t(json_object_get_string(jhttps)));
  }

  *this = res;
  return common::Error();
}

common::Error StreamLink::SerializeFields(json_object* out) const {
  if (http_proxy_) {
    const std::string url_path = http_proxy_->spec();
    json_object_object_add(out, HTTP_FIELD, json_object_new_string(url_path.c_str()));
  }
  if (https_proxy_) {
    const std::string url_path = https_proxy_->spec();
    json_object_object_add(out, HTTPS_FIELD, json_object_new_string(url_path.c_str()));
  }
  return common::Error();
}

}  // namespace fastotv
