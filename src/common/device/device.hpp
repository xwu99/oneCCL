/*
 Copyright 2016-2020 Intel Corporation
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
     http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#pragma once
#include "oneapi/ccl/types_policy.hpp"
#include "oneapi/ccl/types.hpp"
#include "oneapi/ccl/type_traits.hpp"
#include "oneapi/ccl/device_attr_ids.hpp"
#include "oneapi/ccl/device_attr_ids_traits.hpp"
#include "common/utils/utils.hpp"

class ccl_device_impl {
public:
    using device_native_handle_t = typename ccl::unified_device_type::handle_t;
    using device_native_t = typename ccl::unified_device_type::ccl_native_t;

    ccl_device_impl() = delete;
    ccl_device_impl(const ccl_device_impl& other) = delete;
    ccl_device_impl& operator=(const ccl_device_impl& other) = delete;

    ccl_device_impl(device_native_t& dev, const ccl::library_version& version);
    ccl_device_impl(const device_native_t& dev, const ccl::library_version& version);
    ccl_device_impl(device_native_t&& dev, const ccl::library_version& version);
    ccl_device_impl(device_native_handle_t dev_handle, const ccl::library_version& version);
    ~ccl_device_impl() = default;

    //Export Attributes
    using version_traits_t =
        ccl::detail::ccl_api_type_attr_traits<ccl::device_attr_id, ccl::device_attr_id::version>;
    typename version_traits_t::type set_attribute_value(typename version_traits_t::type val,
                                                        const version_traits_t& t);
    const typename version_traits_t::return_type& get_attribute_value(
        const version_traits_t& id) const;

    using cl_backend_traits_t =
        ccl::detail::ccl_api_type_attr_traits<ccl::device_attr_id, ccl::device_attr_id::cl_backend>;
    const typename cl_backend_traits_t::return_type& get_attribute_value(
        const cl_backend_traits_t& id) const;

    using native_handle_traits_t =
        ccl::detail::ccl_api_type_attr_traits<ccl::device_attr_id,
                                              ccl::device_attr_id::native_handle>;
    typename native_handle_traits_t::return_type& get_attribute_value(
        const native_handle_traits_t& id);

    void build_from_params();

private:
    const ccl::library_version version;
    device_native_t native_device;
    bool creation_is_postponed{ false };
};
