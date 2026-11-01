# Project Structure

```
Enigma-Engine/
├── build
│   ├── _deps
│   │   ├── nlohmann_json-build
│   │   │   ├── CMakeFiles
│   │   │   ├── cmake_install.cmake
│   │   │   ├── nlohmann_json.pc
│   │   │   ├── nlohmann_jsonConfig.cmake
│   │   │   └── nlohmann_jsonConfigVersion.cmake
│   │   ├── nlohmann_json-src
│   │   │   ├── cmake
│   │   │   │   ├── scripts
│   │   │   │   │   └── gen_bazel_build_file.cmake
│   │   │   │   ├── ci.cmake
│   │   │   │   ├── config.cmake.in
│   │   │   │   ├── download_test_data.cmake
│   │   │   │   ├── nlohmann_jsonConfigVersion.cmake.in
│   │   │   │   ├── pkg-config.pc.in
│   │   │   │   └── test.cmake
│   │   │   ├── docs
│   │   │   │   ├── docset
│   │   │   │   │   ├── docset.json
│   │   │   │   │   ├── docSet.sql
│   │   │   │   │   ├── icon.png
│   │   │   │   │   ├── icon@2x.png
│   │   │   │   │   ├── Info.plist
│   │   │   │   │   ├── Makefile
│   │   │   │   │   └── README.md
│   │   │   │   ├── examples
│   │   │   │   │   ├── accept__string.cpp
│   │   │   │   │   ├── accept__string.output
│   │   │   │   │   ├── array_t.cpp
│   │   │   │   │   ├── array_t.output
│   │   │   │   │   ├── array.cpp
│   │   │   │   │   ├── array.output
│   │   │   │   │   ├── at__json_pointer_const.cpp
│   │   │   │   │   ├── at__json_pointer_const.output
│   │   │   │   │   ├── at__json_pointer.cpp
│   │   │   │   │   ├── at__json_pointer.output
│   │   │   │   │   ├── at__keytype_const.c++17.cpp
│   │   │   │   │   ├── at__keytype_const.c++17.output
│   │   │   │   │   ├── at__keytype.c++17.cpp
│   │   │   │   │   ├── at__keytype.c++17.output
│   │   │   │   │   ├── at__object_t_key_type_const.cpp
│   │   │   │   │   ├── at__object_t_key_type_const.output
│   │   │   │   │   ├── at__object_t_key_type.cpp
│   │   │   │   │   ├── at__object_t_key_type.output
│   │   │   │   │   ├── at__size_type_const.cpp
│   │   │   │   │   ├── at__size_type_const.output
│   │   │   │   │   ├── at__size_type.cpp
│   │   │   │   │   ├── at__size_type.output
│   │   │   │   │   ├── back.cpp
│   │   │   │   │   ├── back.output
│   │   │   │   │   ├── basic_json__basic_json.cpp
│   │   │   │   │   ├── basic_json__basic_json.output
│   │   │   │   │   ├── basic_json__CompatibleType.cpp
│   │   │   │   │   ├── basic_json__CompatibleType.output
│   │   │   │   │   ├── basic_json__copyassignment.cpp
│   │   │   │   │   ├── basic_json__copyassignment.output
│   │   │   │   │   ├── basic_json__InputIt_InputIt.cpp
│   │   │   │   │   ├── basic_json__InputIt_InputIt.output
│   │   │   │   │   ├── basic_json__list_init_t.cpp
│   │   │   │   │   ├── basic_json__list_init_t.output
│   │   │   │   │   ├── basic_json__moveconstructor.cpp
│   │   │   │   │   ├── basic_json__moveconstructor.output
│   │   │   │   │   ├── basic_json__nullptr_t.cpp
│   │   │   │   │   ├── basic_json__nullptr_t.output
│   │   │   │   │   ├── basic_json__size_type_basic_json.cpp
│   │   │   │   │   ├── basic_json__size_type_basic_json.output
│   │   │   │   │   ├── basic_json__value_t.cpp
│   │   │   │   │   ├── basic_json__value_t.output
│   │   │   │   │   ├── begin.cpp
│   │   │   │   │   ├── begin.output
│   │   │   │   │   ├── binary_t.cpp
│   │   │   │   │   ├── binary_t.output
│   │   │   │   │   ├── binary.cpp
│   │   │   │   │   ├── binary.output
│   │   │   │   │   ├── boolean_t.cpp
│   │   │   │   │   ├── boolean_t.output
│   │   │   │   │   ├── byte_container_with_subtype__byte_container_with_subtype.cpp
│   │   │   │   │   ├── byte_container_with_subtype__byte_container_with_subtype.output
│   │   │   │   │   ├── byte_container_with_subtype__clear_subtype.cpp
│   │   │   │   │   ├── byte_container_with_subtype__clear_subtype.output
│   │   │   │   │   ├── byte_container_with_subtype__has_subtype.cpp
│   │   │   │   │   ├── byte_container_with_subtype__has_subtype.output
│   │   │   │   │   ├── byte_container_with_subtype__set_subtype.cpp
│   │   │   │   │   ├── byte_container_with_subtype__set_subtype.output
│   │   │   │   │   ├── byte_container_with_subtype__subtype.cpp
│   │   │   │   │   ├── byte_container_with_subtype__subtype.output
│   │   │   │   │   ├── cbegin.cpp
│   │   │   │   │   ├── cbegin.output
│   │   │   │   │   ├── cbor_tag_handler_t.cpp
│   │   │   │   │   ├── cbor_tag_handler_t.output
│   │   │   │   │   ├── cend.cpp
│   │   │   │   │   ├── cend.output
│   │   │   │   │   ├── clear.cpp
│   │   │   │   │   ├── clear.output
│   │   │   │   │   ├── contains__json_pointer.cpp
│   │   │   │   │   ├── contains__json_pointer.output
│   │   │   │   │   ├── contains__keytype.c++17.cpp
│   │   │   │   │   ├── contains__keytype.c++17.output
│   │   │   │   │   ├── contains__object_t_key_type.cpp
│   │   │   │   │   ├── contains__object_t_key_type.output
│   │   │   │   │   ├── count__keytype.c++17.cpp
│   │   │   │   │   ├── count__keytype.c++17.output
│   │   │   │   │   ├── count__object_t_key_type.cpp
│   │   │   │   │   ├── count__object_t_key_type.output
│   │   │   │   │   ├── crbegin.cpp
│   │   │   │   │   ├── crbegin.output
│   │   │   │   │   ├── crend.cpp
│   │   │   │   │   ├── crend.output
│   │   │   │   │   ├── default_object_comparator_t.cpp
│   │   │   │   │   ├── default_object_comparator_t.output
│   │   │   │   │   ├── diagnostics_extended.cpp
│   │   │   │   │   ├── diagnostics_extended.output
│   │   │   │   │   ├── diagnostics_standard.cpp
│   │   │   │   │   ├── diagnostics_standard.output
│   │   │   │   │   ├── diff.cpp
│   │   │   │   │   ├── diff.output
│   │   │   │   │   ├── dump.cpp
│   │   │   │   │   ├── dump.output
│   │   │   │   │   ├── emplace_back.cpp
│   │   │   │   │   ├── emplace_back.output
│   │   │   │   │   ├── emplace.cpp
│   │   │   │   │   ├── emplace.output
│   │   │   │   │   ├── empty.cpp
│   │   │   │   │   ├── empty.output
│   │   │   │   │   ├── end.cpp
│   │   │   │   │   ├── end.output
│   │   │   │   │   ├── erase__IteratorType_IteratorType.cpp
│   │   │   │   │   ├── erase__IteratorType_IteratorType.output
│   │   │   │   │   ├── erase__IteratorType.cpp
│   │   │   │   │   ├── erase__IteratorType.output
│   │   │   │   │   ├── erase__keytype.c++17.cpp
│   │   │   │   │   ├── erase__keytype.c++17.output
│   │   │   │   │   ├── erase__object_t_key_type.cpp
│   │   │   │   │   ├── erase__object_t_key_type.output
│   │   │   │   │   ├── erase__size_type.cpp
│   │   │   │   │   ├── erase__size_type.output
│   │   │   │   │   ├── error_handler_t.cpp
│   │   │   │   │   ├── error_handler_t.output
│   │   │   │   │   ├── exception.cpp
│   │   │   │   │   ├── exception.output
│   │   │   │   │   ├── find__keytype.c++17.cpp
│   │   │   │   │   ├── find__keytype.c++17.output
│   │   │   │   │   ├── find__object_t_key_type.cpp
│   │   │   │   │   ├── find__object_t_key_type.output
│   │   │   │   │   ├── flatten.cpp
│   │   │   │   │   ├── flatten.output
│   │   │   │   │   ├── from_bjdata.cpp
│   │   │   │   │   ├── from_bjdata.output
│   │   │   │   │   ├── from_bson.cpp
│   │   │   │   │   ├── from_bson.output
│   │   │   │   │   ├── from_cbor.cpp
│   │   │   │   │   ├── from_cbor.output
│   │   │   │   │   ├── from_json__default_constructible.cpp
│   │   │   │   │   ├── from_json__default_constructible.output
│   │   │   │   │   ├── from_json__non_default_constructible.cpp
│   │   │   │   │   ├── from_json__non_default_constructible.output
│   │   │   │   │   ├── from_msgpack.cpp
│   │   │   │   │   ├── from_msgpack.output
│   │   │   │   │   ├── from_ubjson.cpp
│   │   │   │   │   ├── from_ubjson.output
│   │   │   │   │   ├── front.cpp
│   │   │   │   │   ├── front.output
│   │   │   │   │   ├── get__PointerType.cpp
│   │   │   │   │   ├── get__PointerType.output
│   │   │   │   │   ├── get__ValueType_const.cpp
│   │   │   │   │   ├── get__ValueType_const.output
│   │   │   │   │   ├── get_allocator.cpp
│   │   │   │   │   ├── get_allocator.output
│   │   │   │   │   ├── get_binary.cpp
│   │   │   │   │   ├── get_binary.output
│   │   │   │   │   ├── get_ptr.cpp
│   │   │   │   │   ├── get_ptr.output
│   │   │   │   │   ├── get_ref.cpp
│   │   │   │   │   ├── get_ref.output
│   │   │   │   │   ├── get_to.cpp
│   │   │   │   │   ├── get_to.output
│   │   │   │   │   ├── insert__count.cpp
│   │   │   │   │   ├── insert__count.output
│   │   │   │   │   ├── insert__ilist.cpp
│   │   │   │   │   ├── insert__ilist.output
│   │   │   │   │   ├── insert__range_object.cpp
│   │   │   │   │   ├── insert__range_object.output
│   │   │   │   │   ├── insert__range.cpp
│   │   │   │   │   ├── insert__range.output
│   │   │   │   │   ├── insert.cpp
│   │   │   │   │   ├── insert.output
│   │   │   │   │   ├── invalid_iterator.cpp
│   │   │   │   │   ├── invalid_iterator.output
│   │   │   │   │   ├── is_array.cpp
│   │   │   │   │   ├── is_array.output
│   │   │   │   │   ├── is_binary.cpp
│   │   │   │   │   ├── is_binary.output
│   │   │   │   │   ├── is_boolean.cpp
│   │   │   │   │   ├── is_boolean.output
│   │   │   │   │   ├── is_discarded.cpp
│   │   │   │   │   ├── is_discarded.output
│   │   │   │   │   ├── is_null.cpp
│   │   │   │   │   ├── is_null.output
│   │   │   │   │   ├── is_number_float.cpp
│   │   │   │   │   ├── is_number_float.output
│   │   │   │   │   ├── is_number_integer.cpp
│   │   │   │   │   ├── is_number_integer.output
│   │   │   │   │   ├── is_number_unsigned.cpp
│   │   │   │   │   ├── is_number_unsigned.output
│   │   │   │   │   ├── is_number.cpp
│   │   │   │   │   ├── is_number.output
│   │   │   │   │   ├── is_object.cpp
│   │   │   │   │   ├── is_object.output
│   │   │   │   │   ├── is_primitive.cpp
│   │   │   │   │   ├── is_primitive.output
│   │   │   │   │   ├── is_string.cpp
│   │   │   │   │   ├── is_string.output
│   │   │   │   │   ├── is_structured.cpp
│   │   │   │   │   ├── is_structured.output
│   │   │   │   │   ├── items.cpp
│   │   │   │   │   ├── items.output
│   │   │   │   │   ├── json_base_class_t.cpp
│   │   │   │   │   ├── json_base_class_t.output
│   │   │   │   │   ├── json_lines.cpp
│   │   │   │   │   ├── json_lines.output
│   │   │   │   │   ├── json_pointer__back.cpp
│   │   │   │   │   ├── json_pointer__back.output
│   │   │   │   │   ├── json_pointer__empty.cpp
│   │   │   │   │   ├── json_pointer__empty.output
│   │   │   │   │   ├── json_pointer__operator__equal_stringtype.cpp
│   │   │   │   │   ├── json_pointer__operator__equal_stringtype.output
│   │   │   │   │   ├── json_pointer__operator__equal.cpp
│   │   │   │   │   ├── json_pointer__operator__equal.output
│   │   │   │   │   ├── json_pointer__operator__notequal_stringtype.cpp
│   │   │   │   │   ├── json_pointer__operator__notequal_stringtype.output
│   │   │   │   │   ├── json_pointer__operator__notequal.cpp
│   │   │   │   │   ├── json_pointer__operator__notequal.output
│   │   │   │   │   ├── json_pointer__operator_add_binary.cpp
│   │   │   │   │   ├── json_pointer__operator_add_binary.output
│   │   │   │   │   ├── json_pointer__operator_add.cpp
│   │   │   │   │   ├── json_pointer__operator_add.output
│   │   │   │   │   ├── json_pointer__operator_string_t.cpp
│   │   │   │   │   ├── json_pointer__operator_string_t.output
│   │   │   │   │   ├── json_pointer__parent_pointer.cpp
│   │   │   │   │   ├── json_pointer__parent_pointer.output
│   │   │   │   │   ├── json_pointer__pop_back.cpp
│   │   │   │   │   ├── json_pointer__pop_back.output
│   │   │   │   │   ├── json_pointer__push_back.cpp
│   │   │   │   │   ├── json_pointer__push_back.output
│   │   │   │   │   ├── json_pointer__string_t.cpp
│   │   │   │   │   ├── json_pointer__string_t.output
│   │   │   │   │   ├── json_pointer__to_string.cpp
│   │   │   │   │   ├── json_pointer__to_string.output
│   │   │   │   │   ├── json_pointer.cpp
│   │   │   │   │   ├── json_pointer.output
│   │   │   │   │   ├── max_size.cpp
│   │   │   │   │   ├── max_size.output
│   │   │   │   │   ├── merge_patch.cpp
│   │   │   │   │   ├── merge_patch.output
│   │   │   │   │   ├── meta.cpp
│   │   │   │   │   ├── meta.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_macro.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_only_serialize_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_only_serialize_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_only_serialize_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_only_serialize_macro.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_with_default_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_with_default_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_intrusive_with_default_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_intrusive_with_default_macro.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_macro.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_only_serialize_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_only_serialize_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_only_serialize_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_only_serialize_macro.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_with_default_explicit.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_with_default_explicit.output
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_with_default_macro.cpp
│   │   │   │   │   ├── nlohmann_define_type_non_intrusive_with_default_macro.output
│   │   │   │   │   ├── nlohmann_json_namespace_begin.c++17.cpp
│   │   │   │   │   ├── nlohmann_json_namespace_begin.c++17.output
│   │   │   │   │   ├── nlohmann_json_namespace_no_version.cpp
│   │   │   │   │   ├── nlohmann_json_namespace_no_version.output
│   │   │   │   │   ├── nlohmann_json_namespace.cpp
│   │   │   │   │   ├── nlohmann_json_namespace.output
│   │   │   │   │   ├── nlohmann_json_serialize_enum_2.cpp
│   │   │   │   │   ├── nlohmann_json_serialize_enum_2.output
│   │   │   │   │   ├── nlohmann_json_serialize_enum.cpp
│   │   │   │   │   ├── nlohmann_json_serialize_enum.output
│   │   │   │   │   ├── nlohmann_json_version.cpp
│   │   │   │   │   ├── nlohmann_json_version.output
│   │   │   │   │   ├── number_float_t.cpp
│   │   │   │   │   ├── number_float_t.output
│   │   │   │   │   ├── number_integer_t.cpp
│   │   │   │   │   ├── number_integer_t.output
│   │   │   │   │   ├── number_unsigned_t.cpp
│   │   │   │   │   ├── number_unsigned_t.output
│   │   │   │   │   ├── object_comparator_t.cpp
│   │   │   │   │   ├── object_comparator_t.output
│   │   │   │   │   ├── object_t.cpp
│   │   │   │   │   ├── object_t.output
│   │   │   │   │   ├── object.cpp
│   │   │   │   │   ├── object.output
│   │   │   │   │   ├── operator__equal__nullptr_t.cpp
│   │   │   │   │   ├── operator__equal__nullptr_t.output
│   │   │   │   │   ├── operator__equal__specializations.cpp
│   │   │   │   │   ├── operator__equal__specializations.output
│   │   │   │   │   ├── operator__equal.cpp
│   │   │   │   │   ├── operator__equal.output
│   │   │   │   │   ├── operator__greater.cpp
│   │   │   │   │   ├── operator__greater.output
│   │   │   │   │   ├── operator__greaterequal.cpp
│   │   │   │   │   ├── operator__greaterequal.output
│   │   │   │   │   ├── operator__less.cpp
│   │   │   │   │   ├── operator__less.output
│   │   │   │   │   ├── operator__lessequal.cpp
│   │   │   │   │   ├── operator__lessequal.output
│   │   │   │   │   ├── operator__notequal__nullptr_t.cpp
│   │   │   │   │   ├── operator__notequal__nullptr_t.output
│   │   │   │   │   ├── operator__notequal.cpp
│   │   │   │   │   ├── operator__notequal.output
│   │   │   │   │   ├── operator__value_t.cpp
│   │   │   │   │   ├── operator__value_t.output
│   │   │   │   │   ├── operator__ValueType.cpp
│   │   │   │   │   ├── operator__ValueType.output
│   │   │   │   │   ├── operator_array__json_pointer_const.cpp
│   │   │   │   │   ├── operator_array__json_pointer_const.output
│   │   │   │   │   ├── operator_array__json_pointer.cpp
│   │   │   │   │   ├── operator_array__json_pointer.output
│   │   │   │   │   ├── operator_array__keytype_const.c++17.cpp
│   │   │   │   │   ├── operator_array__keytype_const.c++17.output
│   │   │   │   │   ├── operator_array__keytype.c++17.cpp
│   │   │   │   │   ├── operator_array__keytype.c++17.output
│   │   │   │   │   ├── operator_array__object_t_key_type_const.cpp
│   │   │   │   │   ├── operator_array__object_t_key_type_const.output
│   │   │   │   │   ├── operator_array__object_t_key_type.cpp
│   │   │   │   │   ├── operator_array__object_t_key_type.output
│   │   │   │   │   ├── operator_array__size_type_const.cpp
│   │   │   │   │   ├── operator_array__size_type_const.output
│   │   │   │   │   ├── operator_array__size_type.cpp
│   │   │   │   │   ├── operator_array__size_type.output
│   │   │   │   │   ├── operator_deserialize.cpp
│   │   │   │   │   ├── operator_deserialize.output
│   │   │   │   │   ├── operator_literal_json_pointer.cpp
│   │   │   │   │   ├── operator_literal_json_pointer.output
│   │   │   │   │   ├── operator_literal_json.cpp
│   │   │   │   │   ├── operator_literal_json.output
│   │   │   │   │   ├── operator_ltlt__basic_json.cpp
│   │   │   │   │   ├── operator_ltlt__basic_json.output
│   │   │   │   │   ├── operator_ltlt__json_pointer.cpp
│   │   │   │   │   ├── operator_ltlt__json_pointer.output
│   │   │   │   │   ├── operator_spaceship__const_reference.c++20.cpp
│   │   │   │   │   ├── operator_spaceship__const_reference.c++20.output
│   │   │   │   │   ├── operator_spaceship__scalartype.c++20.cpp
│   │   │   │   │   ├── operator_spaceship__scalartype.c++20.output
│   │   │   │   │   ├── ordered_json.cpp
│   │   │   │   │   ├── ordered_json.output
│   │   │   │   │   ├── ordered_map.cpp
│   │   │   │   │   ├── ordered_map.output
│   │   │   │   │   ├── other_error.cpp
│   │   │   │   │   ├── other_error.output
│   │   │   │   │   ├── out_of_range.cpp
│   │   │   │   │   ├── out_of_range.output
│   │   │   │   │   ├── parse__allow_exceptions.cpp
│   │   │   │   │   ├── parse__allow_exceptions.output
│   │   │   │   │   ├── parse__array__parser_callback_t.cpp
│   │   │   │   │   ├── parse__array__parser_callback_t.output
│   │   │   │   │   ├── parse__contiguouscontainer__parser_callback_t.cpp
│   │   │   │   │   ├── parse__contiguouscontainer__parser_callback_t.output
│   │   │   │   │   ├── parse__istream__parser_callback_t.cpp
│   │   │   │   │   ├── parse__istream__parser_callback_t.output
│   │   │   │   │   ├── parse__iterator_pair.cpp
│   │   │   │   │   ├── parse__iterator_pair.link
│   │   │   │   │   ├── parse__iterator_pair.output
│   │   │   │   │   ├── parse__pointers.cpp
│   │   │   │   │   ├── parse__pointers.link
│   │   │   │   │   ├── parse__pointers.output
│   │   │   │   │   ├── parse__string__parser_callback_t.cpp
│   │   │   │   │   ├── parse__string__parser_callback_t.output
│   │   │   │   │   ├── parse_error.cpp
│   │   │   │   │   ├── parse_error.output
│   │   │   │   │   ├── patch_inplace.cpp
│   │   │   │   │   ├── patch_inplace.output
│   │   │   │   │   ├── patch.cpp
│   │   │   │   │   ├── patch.output
│   │   │   │   │   ├── push_back__initializer_list.cpp
│   │   │   │   │   ├── push_back__initializer_list.output
│   │   │   │   │   ├── push_back__object_t__value.cpp
│   │   │   │   │   ├── push_back__object_t__value.output
│   │   │   │   │   ├── push_back.cpp
│   │   │   │   │   ├── push_back.output
│   │   │   │   │   ├── rbegin.cpp
│   │   │   │   │   ├── rbegin.output
│   │   │   │   │   ├── README.cpp
│   │   │   │   │   ├── README.output
│   │   │   │   │   ├── rend.cpp
│   │   │   │   │   ├── rend.output
│   │   │   │   │   ├── sax_parse__binary.cpp
│   │   │   │   │   ├── sax_parse__binary.output
│   │   │   │   │   ├── sax_parse.cpp
│   │   │   │   │   ├── sax_parse.output
│   │   │   │   │   ├── size.cpp
│   │   │   │   │   ├── size.output
│   │   │   │   │   ├── std_hash.cpp
│   │   │   │   │   ├── std_hash.output
│   │   │   │   │   ├── std_swap.cpp
│   │   │   │   │   ├── std_swap.output
│   │   │   │   │   ├── string_t.cpp
│   │   │   │   │   ├── string_t.output
│   │   │   │   │   ├── swap__array_t.cpp
│   │   │   │   │   ├── swap__array_t.output
│   │   │   │   │   ├── swap__binary_t.cpp
│   │   │   │   │   ├── swap__binary_t.output
│   │   │   │   │   ├── swap__object_t.cpp
│   │   │   │   │   ├── swap__object_t.output
│   │   │   │   │   ├── swap__reference.cpp
│   │   │   │   │   ├── swap__reference.output
│   │   │   │   │   ├── swap__string_t.cpp
│   │   │   │   │   ├── swap__string_t.output
│   │   │   │   │   ├── to_bjdata.cpp
│   │   │   │   │   ├── to_bjdata.output
│   │   │   │   │   ├── to_bson.cpp
│   │   │   │   │   ├── to_bson.output
│   │   │   │   │   ├── to_cbor.cpp
│   │   │   │   │   ├── to_cbor.output
│   │   │   │   │   ├── to_json.cpp
│   │   │   │   │   ├── to_json.output
│   │   │   │   │   ├── to_msgpack.cpp
│   │   │   │   │   ├── to_msgpack.output
│   │   │   │   │   ├── to_string.cpp
│   │   │   │   │   ├── to_string.output
│   │   │   │   │   ├── to_ubjson.cpp
│   │   │   │   │   ├── to_ubjson.output
│   │   │   │   │   ├── type_error.cpp
│   │   │   │   │   ├── type_error.output
│   │   │   │   │   ├── type_name.cpp
│   │   │   │   │   ├── type_name.output
│   │   │   │   │   ├── type.cpp
│   │   │   │   │   ├── type.output
│   │   │   │   │   ├── unflatten.cpp
│   │   │   │   │   ├── unflatten.output
│   │   │   │   │   ├── update__range.cpp
│   │   │   │   │   ├── update__range.output
│   │   │   │   │   ├── update.cpp
│   │   │   │   │   ├── update.output
│   │   │   │   │   ├── value__json_ptr.cpp
│   │   │   │   │   ├── value__json_ptr.output
│   │   │   │   │   ├── value__keytype.c++17.cpp
│   │   │   │   │   ├── value__keytype.c++17.output
│   │   │   │   │   ├── value__object_t_key_type.cpp
│   │   │   │   │   └── value__object_t_key_type.output
│   │   │   │   ├── mkdocs
│   │   │   │   │   ├── docs
│   │   │   │   │   ├── scripts
│   │   │   │   │   ├── Makefile
│   │   │   │   │   ├── mkdocs.yml
│   │   │   │   │   └── requirements.txt
│   │   │   │   ├── usages
│   │   │   │   │   ├── ios.png
│   │   │   │   │   └── macos.png
│   │   │   │   ├── avatars.png
│   │   │   │   ├── json.gif
│   │   │   │   ├── Makefile
│   │   │   │   └── README.md
│   │   │   ├── include
│   │   │   │   └── nlohmann
│   │   │   │       ├── detail
│   │   │   │       ├── thirdparty
│   │   │   │       ├── adl_serializer.hpp
│   │   │   │       ├── byte_container_with_subtype.hpp
│   │   │   │       ├── json_fwd.hpp
│   │   │   │       ├── json.hpp
│   │   │   │       └── ordered_map.hpp
│   │   │   ├── LICENSES
│   │   │   │   ├── Apache-2.0.txt
│   │   │   │   ├── BSD-3-Clause.txt
│   │   │   │   ├── GPL-3.0-only.txt
│   │   │   │   └── MIT.txt
│   │   │   ├── single_include
│   │   │   │   └── nlohmann
│   │   │   │       ├── json_fwd.hpp
│   │   │   │       └── json.hpp
│   │   │   ├── tests
│   │   │   │   ├── abi
│   │   │   │   │   ├── config
│   │   │   │   │   ├── diag
│   │   │   │   │   ├── include
│   │   │   │   │   ├── inline_ns
│   │   │   │   │   ├── CMakeLists.txt
│   │   │   │   │   └── main.cpp
│   │   │   │   ├── benchmarks
│   │   │   │   │   ├── src
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_add_subdirectory
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_fetch_content
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_fetch_content2
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_import
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_import_minver
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cmake_target_include_directories
│   │   │   │   │   ├── project
│   │   │   │   │   └── CMakeLists.txt
│   │   │   │   ├── cuda_example
│   │   │   │   │   ├── CMakeLists.txt
│   │   │   │   │   └── json_cuda.cu
│   │   │   │   ├── reports
│   │   │   │   │   ├── 2016-08-29-fuzz
│   │   │   │   │   ├── 2016-09-09-nativejson_benchmark
│   │   │   │   │   └── 2016-10-02-fuzz
│   │   │   │   ├── src
│   │   │   │   │   ├── fuzzer-driver_afl.cpp
│   │   │   │   │   ├── fuzzer-parse_bjdata.cpp
│   │   │   │   │   ├── fuzzer-parse_bson.cpp
│   │   │   │   │   ├── fuzzer-parse_cbor.cpp
│   │   │   │   │   ├── fuzzer-parse_json.cpp
│   │   │   │   │   ├── fuzzer-parse_msgpack.cpp
│   │   │   │   │   ├── fuzzer-parse_ubjson.cpp
│   │   │   │   │   ├── make_test_data_available.hpp
│   │   │   │   │   ├── test_utils.hpp
│   │   │   │   │   ├── unit-32bit.cpp
│   │   │   │   │   ├── unit-algorithms.cpp
│   │   │   │   │   ├── unit-allocator.cpp
│   │   │   │   │   ├── unit-alt-string.cpp
│   │   │   │   │   ├── unit-assert_macro.cpp
│   │   │   │   │   ├── unit-binary_formats.cpp
│   │   │   │   │   ├── unit-bjdata.cpp
│   │   │   │   │   ├── unit-bson.cpp
│   │   │   │   │   ├── unit-byte_container_with_subtype.cpp
│   │   │   │   │   ├── unit-capacity.cpp
│   │   │   │   │   ├── unit-cbor.cpp
│   │   │   │   │   ├── unit-class_const_iterator.cpp
│   │   │   │   │   ├── unit-class_iterator.cpp
│   │   │   │   │   ├── unit-class_lexer.cpp
│   │   │   │   │   ├── unit-class_parser.cpp
│   │   │   │   │   ├── unit-comparison.cpp
│   │   │   │   │   ├── unit-concepts.cpp
│   │   │   │   │   ├── unit-constructor1.cpp
│   │   │   │   │   ├── unit-constructor2.cpp
│   │   │   │   │   ├── unit-convenience.cpp
│   │   │   │   │   ├── unit-conversions.cpp
│   │   │   │   │   ├── unit-custom-base-class.cpp
│   │   │   │   │   ├── unit-deserialization.cpp
│   │   │   │   │   ├── unit-diagnostics.cpp
│   │   │   │   │   ├── unit-disabled_exceptions.cpp
│   │   │   │   │   ├── unit-element_access1.cpp
│   │   │   │   │   ├── unit-element_access2.cpp
│   │   │   │   │   ├── unit-hash.cpp
│   │   │   │   │   ├── unit-inspection.cpp
│   │   │   │   │   ├── unit-items.cpp
│   │   │   │   │   ├── unit-iterators1.cpp
│   │   │   │   │   ├── unit-iterators2.cpp
│   │   │   │   │   ├── unit-json_patch.cpp
│   │   │   │   │   ├── unit-json_pointer.cpp
│   │   │   │   │   ├── unit-large_json.cpp
│   │   │   │   │   ├── unit-merge_patch.cpp
│   │   │   │   │   ├── unit-meta.cpp
│   │   │   │   │   ├── unit-modifiers.cpp
│   │   │   │   │   ├── unit-msgpack.cpp
│   │   │   │   │   ├── unit-no-mem-leak-on-adl-serialize.cpp
│   │   │   │   │   ├── unit-noexcept.cpp
│   │   │   │   │   ├── unit-ordered_json.cpp
│   │   │   │   │   ├── unit-ordered_map.cpp
│   │   │   │   │   ├── unit-pointer_access.cpp
│   │   │   │   │   ├── unit-readme.cpp
│   │   │   │   │   ├── unit-reference_access.cpp
│   │   │   │   │   ├── unit-regression1.cpp
│   │   │   │   │   ├── unit-regression2.cpp
│   │   │   │   │   ├── unit-serialization.cpp
│   │   │   │   │   ├── unit-testsuites.cpp
│   │   │   │   │   ├── unit-to_chars.cpp
│   │   │   │   │   ├── unit-type_traits.cpp
│   │   │   │   │   ├── unit-ubjson.cpp
│   │   │   │   │   ├── unit-udl.cpp
│   │   │   │   │   ├── unit-udt_macro.cpp
│   │   │   │   │   ├── unit-udt.cpp
│   │   │   │   │   ├── unit-unicode1.cpp
│   │   │   │   │   ├── unit-unicode2.cpp
│   │   │   │   │   ├── unit-unicode3.cpp
│   │   │   │   │   ├── unit-unicode4.cpp
│   │   │   │   │   ├── unit-unicode5.cpp
│   │   │   │   │   ├── unit-user_defined_input.cpp
│   │   │   │   │   ├── unit-windows_h.cpp
│   │   │   │   │   ├── unit-wstring.cpp
│   │   │   │   │   └── unit.cpp
│   │   │   │   ├── thirdparty
│   │   │   │   │   ├── doctest
│   │   │   │   │   ├── fifo_map
│   │   │   │   │   ├── Fuzzer
│   │   │   │   │   └── imapdl
│   │   │   │   ├── CMakeLists.txt
│   │   │   │   ├── fuzzing.md
│   │   │   │   └── Makefile
│   │   │   ├── tools
│   │   │   │   ├── amalgamate
│   │   │   │   │   ├── amalgamate.py
│   │   │   │   │   ├── CHANGES.md
│   │   │   │   │   ├── config_json_fwd.json
│   │   │   │   │   ├── config_json.json
│   │   │   │   │   └── README.md
│   │   │   │   ├── gdb_pretty_printer
│   │   │   │   │   ├── nlohmann-json.py
│   │   │   │   │   └── README.md
│   │   │   │   ├── generate_natvis
│   │   │   │   │   ├── generate_natvis.py
│   │   │   │   │   ├── nlohmann_json.natvis.j2
│   │   │   │   │   └── README.md
│   │   │   │   ├── macro_builder
│   │   │   │   │   └── main.cpp
│   │   │   │   └── serve_header
│   │   │   │       ├── demo.png
│   │   │   │       ├── README.md
│   │   │   │       ├── requirements.txt
│   │   │   │       ├── serve_header.py
│   │   │   │       └── serve_header.yml.example
│   │   │   ├── BUILD.bazel
│   │   │   ├── ChangeLog.md
│   │   │   ├── CITATION.cff
│   │   │   ├── CMakeLists.txt
│   │   │   ├── LICENSE.MIT
│   │   │   ├── Makefile
│   │   │   ├── meson.build
│   │   │   ├── nlohmann_json.natvis
│   │   │   ├── Package.swift
│   │   │   ├── README.md
│   │   │   ├── WORKSPACE.bazel
│   │   │   └── wsjcpp.yml
│   │   └── nlohmann_json-subbuild
│   │       ├── CMakeFiles
│   │       │   ├── 4.3.2
│   │       │   │   └── CMakeSystem.cmake
│   │       │   ├── 4.3.4
│   │       │   │   └── CMakeSystem.cmake
│   │       │   ├── 4.4.2
│   │       │   │   └── CMakeSystem.cmake
│   │       │   ├── nlohmann_json-populate.dir
│   │       │   │   ├── Labels.json
│   │       │   │   └── Labels.txt
│   │       │   ├── pkgRedirects
│   │       │   ├── cmake.check_cache
│   │       │   ├── CMakeConfigureLog.yaml
│   │       │   ├── InstallScripts.json
│   │       │   ├── nlohmann_json-populate-complete
│   │       │   ├── rules.ninja
│   │       │   └── TargetDirectories.txt
│   │       ├── nlohmann_json-populate-prefix
│   │       │   ├── src
│   │       │   │   └── nlohmann_json-populate-stamp
│   │       │   └── tmp
│   │       │       ├── nlohmann_json-populate-cfgcmd.txt
│   │       │       ├── nlohmann_json-populate-gitclone.cmake
│   │       │       ├── nlohmann_json-populate-gitupdate.cmake
│   │       │       └── nlohmann_json-populate-mkdirs.cmake
│   │       ├── build.ninja
│   │       ├── cmake_install.cmake
│   │       ├── CMakeCache.txt
│   │       └── CMakeLists.txt
│   ├── CMakeFiles
│   │   ├── 4.3.2
│   │   │   ├── CompilerIdC
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   ├── CompilerIdCXX
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCXXCompilerId.cpp
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeRCCompiler.cmake
│   │   │   └── CMakeSystem.cmake
│   │   ├── 4.3.4
│   │   │   ├── CompilerIdC
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   ├── CompilerIdCXX
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCXXCompilerId.cpp
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeRCCompiler.cmake
│   │   │   └── CMakeSystem.cmake
│   │   ├── 4.4.2
│   │   │   ├── CompilerIdC
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   ├── CompilerIdCXX
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCXXCompilerId.cpp
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeRCCompiler.cmake
│   │   │   └── CMakeSystem.cmake
│   │   ├── d
│   │   ├── decompiler.dir
│   │   │   └── src
│   │   │       └── decompiler
│   │   │           ├── action.cc.obj
│   │   │           ├── address.cc.obj
│   │   │           ├── analyzesigs.cc.obj
│   │   │           ├── architecture.cc.obj
│   │   │           ├── bfd_arch.cc.obj
│   │   │           ├── bitfield.cc.obj
│   │   │           ├── block.cc.obj
│   │   │           ├── blockaction.cc.obj
│   │   │           ├── callgraph.cc.obj
│   │   │           ├── capability.cc.obj
│   │   │           ├── cast.cc.obj
│   │   │           ├── codedata.cc.obj
│   │   │           ├── comment_ghidra.cc.obj
│   │   │           ├── comment.cc.obj
│   │   │           ├── compression.cc.obj
│   │   │           ├── condexe.cc.obj
│   │   │           ├── consolemain.cc.obj
│   │   │           ├── constseq.cc.obj
│   │   │           ├── context.cc.obj
│   │   │           ├── coreaction.cc.obj
│   │   │           ├── cover.cc.obj
│   │   │           ├── cpool_ghidra.cc.obj
│   │   │           ├── cpool.cc.obj
│   │   │           ├── crc32.cc.obj
│   │   │           ├── database_ghidra.cc.obj
│   │   │           ├── database.cc.obj
│   │   │           ├── double.cc.obj
│   │   │           ├── dynamic.cc.obj
│   │   │           ├── emulate.cc.obj
│   │   │           ├── emulateutil.cc.obj
│   │   │           ├── expression.cc.obj
│   │   │           ├── filemanage.cc.obj
│   │   │           ├── float.cc.obj
│   │   │           ├── flow.cc.obj
│   │   │           ├── fspec.cc.obj
│   │   │           ├── funcdata_block.cc.obj
│   │   │           ├── funcdata_op.cc.obj
│   │   │           ├── funcdata_varnode.cc.obj
│   │   │           ├── funcdata.cc.obj
│   │   │           ├── ghidra_arch.cc.obj
│   │   │           ├── ghidra_context.cc.obj
│   │   │           ├── ghidra_process.cc.obj
│   │   │           ├── ghidra_translate.cc.obj
│   │   │           ├── globalcontext.cc.obj
│   │   │           ├── grammar.cc.obj
│   │   │           ├── graph.cc.obj
│   │   │           ├── heritage.cc.obj
│   │   │           ├── ifacedecomp.cc.obj
│   │   │           ├── ifaceterm.cc.obj
│   │   │           ├── inject_ghidra.cc.obj
│   │   │           ├── inject_sleigh.cc.obj
│   │   │           ├── interface.cc.obj
│   │   │           ├── jumptable.cc.obj
│   │   │           ├── libdecomp.cc.obj
│   │   │           ├── loadimage_bfd.cc.obj
│   │   │           ├── loadimage_ghidra.cc.obj
│   │   │           ├── loadimage_xml.cc.obj
│   │   │           ├── loadimage.cc.obj
│   │   │           ├── marshal.cc.obj
│   │   │           ├── memstate.cc.obj
│   │   │           ├── merge.cc.obj
│   │   │           ├── modelrules.cc.obj
│   │   │           ├── multiprecision.cc.obj
│   │   │           ├── op.cc.obj
│   │   │           ├── opbehavior.cc.obj
│   │   │           ├── opcodes.cc.obj
│   │   │           ├── options.cc.obj
│   │   │           ├── override.cc.obj
│   │   │           ├── paramid.cc.obj
│   │   │           ├── pcodecompile.cc.obj
│   │   │           ├── pcodeinject.cc.obj
│   │   │           ├── pcodeparse.cc.obj
│   │   │           ├── pcoderaw.cc.obj
│   │   │           ├── prefersplit.cc.obj
│   │   │           ├── prettyprint.cc.obj
│   │   │           ├── printc.cc.obj
│   │   │           ├── printjava.cc.obj
│   │   │           ├── printlanguage.cc.obj
│   │   │           ├── rangeutil.cc.obj
│   │   │           ├── raw_arch.cc.obj
│   │   │           ├── ruleaction.cc.obj
│   │   │           ├── rulecompile.cc.obj
│   │   │           ├── semantics.cc.obj
│   │   │           ├── signature_ghidra.cc.obj
│   │   │           ├── signature.cc.obj
│   │   │           ├── slaformat.cc.obj
│   │   │           ├── sleigh_arch.cc.obj
│   │   │           ├── sleigh.cc.obj
│   │   │           ├── sleighbase.cc.obj
│   │   │           ├── sleighexample.cc.obj
│   │   │           ├── slgh_compile.cc.obj
│   │   │           ├── slghparse.cc.obj
│   │   │           ├── slghpatexpress.cc.obj
│   │   │           ├── slghpattern.cc.obj
│   │   │           ├── slghscan.cc.obj
│   │   │           ├── slghsymbol.cc.obj
│   │   │           ├── space.cc.obj
│   │   │           ├── string_ghidra.cc.obj
│   │   │           ├── stringmanage.cc.obj
│   │   │           ├── subflow.cc.obj
│   │   │           ├── test.cc.obj
│   │   │           ├── testfunction.cc.obj
│   │   │           ├── transform.cc.obj
│   │   │           ├── translate.cc.obj
│   │   │           ├── type.cc.obj
│   │   │           ├── typegrp_ghidra.cc.obj
│   │   │           ├── typeop.cc.obj
│   │   │           ├── unify.cc.obj
│   │   │           ├── unionresolve.cc.obj
│   │   │           ├── userop.cc.obj
│   │   │           ├── variable.cc.obj
│   │   │           ├── varmap.cc.obj
│   │   │           ├── varnode.cc.obj
│   │   │           ├── xml_arch.cc.obj
│   │   │           └── xml.cc.obj
│   │   ├── enigma_binary_audit_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_binary_audit.dir
│   │   │   ├── enigma_binary_audit_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_binary_audit.cpp.obj
│   │   ├── enigma_decompile_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_decompile_full_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_decompile_full.dir
│   │   │   ├── enigma_decompile_full_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_decompile_full.cpp.obj
│   │   ├── enigma_decompile.dir
│   │   │   ├── enigma_decompile_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_decompile.cpp.obj
│   │   ├── enigma_dump_functions_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_dump_functions.dir
│   │   │   ├── enigma_dump_functions_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_dump_functions.cpp.obj
│   │   ├── enigma_dump_listing_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_dump_listing.dir
│   │   │   ├── enigma_dump_listing_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_dump_listing.cpp.obj
│   │   ├── enigma_engine.dir
│   │   │   └── src
│   │   │       ├── address
│   │   │       │   ├── AbstractAddressSetView.cpp.obj
│   │   │       │   ├── Address.cpp.obj
│   │   │       │   ├── AddressCollectors.cpp.obj
│   │   │       │   ├── AddressIterator.cpp.obj
│   │   │       │   ├── AddressIteratorAdapter.cpp.obj
│   │   │       │   ├── AddressMapImpl.cpp.obj
│   │   │       │   ├── AddressObjectMap.cpp.obj
│   │   │       │   ├── AddressRangeImpl.cpp.obj
│   │   │       │   ├── AddressRangeIterator.cpp.obj
│   │   │       │   ├── AddressRangeSplitter.cpp.obj
│   │   │       │   ├── AddressRangeToAddressComparator.cpp.obj
│   │   │       │   ├── AddressSet.cpp.obj
│   │   │       │   ├── AddressSetCollection.cpp.obj
│   │   │       │   ├── AddressSetMapping.cpp.obj
│   │   │       │   ├── AddressSetViewAdapter.cpp.obj
│   │   │       │   ├── AddressSpace.cpp.obj
│   │   │       │   ├── AddressUtils.cpp.obj
│   │   │       │   ├── DifferenceAddressSetView.cpp.obj
│   │   │       │   ├── EmptyAddressIterator.cpp.obj
│   │   │       │   ├── EmptyAddressRangeIterator.cpp.obj
│   │   │       │   ├── ImmutableAddressSet.cpp.obj
│   │   │       │   ├── IntersectionAddressSetView.cpp.obj
│   │   │       │   ├── NormalizedAddressSet.cpp.obj
│   │   │       │   ├── ProtectedAddressSpace.cpp.obj
│   │   │       │   ├── SegmentedAddress.cpp.obj
│   │   │       │   ├── SegmentedAddressSpace.cpp.obj
│   │   │       │   ├── SingleAddressSetCollection.cpp.obj
│   │   │       │   ├── SpecialAddress.cpp.obj
│   │   │       │   ├── SymmetricDifferenceAddressSetView.cpp.obj
│   │   │       │   ├── TwoWayBreakdownAddressRangeIterator.cpp.obj
│   │   │       │   ├── UnionAddressRangeIterator.cpp.obj
│   │   │       │   └── UnionAddressSetView.cpp.obj
│   │   │       ├── block
│   │   │       │   ├── graph
│   │   │       │   ├── BasicBlockModel.cpp.obj
│   │   │       │   ├── CodeBlockCache.cpp.obj
│   │   │       │   ├── CodeBlockImpl.cpp.obj
│   │   │       │   ├── CodeBlockIterator.cpp.obj
│   │   │       │   ├── CodeBlockReferenceImpl.cpp.obj
│   │   │       │   ├── CodeBlockReferenceIterator.cpp.obj
│   │   │       │   ├── ExtCodeBlockImpl.cpp.obj
│   │   │       │   ├── FollowFlow.cpp.obj
│   │   │       │   ├── IsolatedEntrySubModel.cpp.obj
│   │   │       │   ├── MultEntSubIterator.cpp.obj
│   │   │       │   ├── MultEntSubModel.cpp.obj
│   │   │       │   ├── OverlapCodeSubModel.cpp.obj
│   │   │       │   ├── PartitionCodeSubIterator.cpp.obj
│   │   │       │   ├── PartitionCodeSubModel.cpp.obj
│   │   │       │   ├── SimpleBlockIterator.cpp.obj
│   │   │       │   ├── SimpleBlockModel.cpp.obj
│   │   │       │   ├── SimpleDestReferenceIterator.cpp.obj
│   │   │       │   ├── SimpleSourceReferenceIterator.cpp.obj
│   │   │       │   ├── SingleEntSubIterator.cpp.obj
│   │   │       │   ├── SubroutineDestReferenceIterator.cpp.obj
│   │   │       │   └── SubroutineSourceReferenceIterator.cpp.obj
│   │   │       ├── cfg
│   │   │       │   ├── DisassemblyCFG.cpp.obj
│   │   │       │   └── FunctionGraphLayout.cpp.obj
│   │   │       ├── core
│   │   │       │   ├── patch
│   │   │       │   ├── AARCH64PltThunkAnalyzer.cpp.obj
│   │   │       │   ├── AbstractAnalyzer.cpp.obj
│   │   │       │   ├── AbstractBinaryFormatAnalyzer.cpp.obj
│   │   │       │   ├── AbstractDemanglerAnalyzer.cpp.obj
│   │   │       │   ├── AbstractJavaAnalyzer.cpp.obj
│   │   │       │   ├── AddressTableAnalyzer.cpp.obj
│   │   │       │   ├── AggressiveInstructionFinderAnalyzer.cpp.obj
│   │   │       │   ├── AggressiveRecoveryAnalyzer.cpp.obj
│   │   │       │   ├── AnalysisBridge.cpp.obj
│   │   │       │   ├── AnalysisPriority.cpp.obj
│   │   │       │   ├── AnalysisScheduler.cpp.obj
│   │   │       │   ├── AnalysisTaskList.cpp.obj
│   │   │       │   ├── Analyzer.cpp.obj
│   │   │       │   ├── AndroidBootLoaderAnalyzer.cpp.obj
│   │   │       │   ├── Apple8900Analyzer.cpp.obj
│   │   │       │   ├── AppleSingleDoubleAnalyzer.cpp.obj
│   │   │       │   ├── ApplyDataArchiveAnalyzer.cpp.obj
│   │   │       │   ├── ApplyKnownSignatureAnalyzer.cpp.obj
│   │   │       │   ├── ArmAggressiveInstructionFinderAnalyzer.cpp.obj
│   │   │       │   ├── ArmAnalyzer.cpp.obj
│   │   │       │   ├── ArmSymbolAnalyzer.cpp.obj
│   │   │       │   ├── ArtAnalyzer.cpp.obj
│   │   │       │   ├── Assembler.cpp.obj
│   │   │       │   ├── AutoAnalysisManager.cpp.obj
│   │   │       │   ├── BinaryLoader.cpp.obj
│   │   │       │   ├── BinaryPropertyListAnalyzer.cpp.obj
│   │   │       │   ├── BinaryReader.cpp.obj
│   │   │       │   ├── BootImageAnalyzer.cpp.obj
│   │   │       │   ├── CallFixupAnalyzer.cpp.obj
│   │   │       │   ├── CallFixupChangeAnalyzer.cpp.obj
│   │   │       │   ├── CategoryPath.cpp.obj
│   │   │       │   ├── CFStringAnalyzer.cpp.obj
│   │   │       │   ├── CliMetadataTokenAnalyzer.cpp.obj
│   │   │       │   ├── CoffAnalyzer.cpp.obj
│   │   │       │   ├── CoffArchiveAnalyzer.cpp.obj
│   │   │       │   ├── CompilerSpec.cpp.obj
│   │   │       │   ├── CondenseFillerBytesAnalyzer.cpp.obj
│   │   │       │   ├── ConstantPropagationAnalyzer.cpp.obj
│   │   │       │   ├── ConstantPropagationContextEvaluator.cpp.obj
│   │   │       │   ├── ContextEvaluatorAdapter.cpp.obj
│   │   │       │   ├── CramFsAnalyzer.cpp.obj
│   │   │       │   ├── CreateThunkAnalyzer.cpp.obj
│   │   │       │   ├── DataOperandReferenceAnalyzer.cpp.obj
│   │   │       │   ├── DataOrganization.cpp.obj
│   │   │       │   ├── DataRefFunctionAnalyzer.cpp.obj
│   │   │       │   ├── DataSectionFunctionScannerAnalyzer.cpp.obj
│   │   │       │   ├── DecompilerAdapter.cpp.obj
│   │   │       │   ├── DecompilerCallConventionAnalyzer.cpp.obj
│   │   │       │   ├── DecompilerFunctionAnalyzer.cpp.obj
│   │   │       │   ├── DecompilerSwitchAnalyzer.cpp.obj
│   │   │       │   ├── DecompInterface.cpp.obj
│   │   │       │   ├── DexCondenseFillerBytesAnalyzer.cpp.obj
│   │   │       │   ├── DexExceptionHandlersAnalyzer.cpp.obj
│   │   │       │   ├── DexHeaderFormatAnalyzer.cpp.obj
│   │   │       │   ├── DexMarkupDataAnalyzer.cpp.obj
│   │   │       │   ├── DexMarkupInstructionsAnalyzer.cpp.obj
│   │   │       │   ├── DexMarkupSwitchTableAnalyzer.cpp.obj
│   │   │       │   ├── Disassembler.cpp.obj
│   │   │       │   ├── DisassemblyAnalyzer.cpp.obj
│   │   │       │   ├── DmgAnalyzer.cpp.obj
│   │   │       │   ├── DtbAnalyzer.cpp.obj
│   │   │       │   ├── DWARFAnalyzer.cpp.obj
│   │   │       │   ├── DyldCacheAnalyzer.cpp.obj
│   │   │       │   ├── eBPFSyscallAnalyzer.cpp.obj
│   │   │       │   ├── ElfAnalyzer.cpp.obj
│   │   │       │   ├── ElfScalarOperandAnalyzer.cpp.obj
│   │   │       │   ├── EmbeddedMediaAnalyzer.cpp.obj
│   │   │       │   ├── EntryPointAnalyzer.cpp.obj
│   │   │       │   ├── Ext4Analyzer.cpp.obj
│   │   │       │   ├── ExternalEntryFunctionAnalyzer.cpp.obj
│   │   │       │   ├── ExternalSymbolResolver.cpp.obj
│   │   │       │   ├── ExternalSymbolResolverAnalyzer.cpp.obj
│   │   │       │   ├── FBPK_Analyzer.cpp.obj
│   │   │       │   ├── FdtAnalyzer.cpp.obj
│   │   │       │   ├── FidAnalyzer.cpp.obj
│   │   │       │   ├── FidHasher.cpp.obj
│   │   │       │   ├── FileFormatAnalyzer.cpp.obj
│   │   │       │   ├── FindNoReturnFunctionsAnalyzer.cpp.obj
│   │   │       │   ├── FksLibrary.cpp.obj
│   │   │       │   ├── FormatStringAnalyzer.cpp.obj
│   │   │       │   ├── FragmentMergeAnalyzer.cpp.obj
│   │   │       │   ├── FunctionAnalyzer.cpp.obj
│   │   │       │   ├── FunctionBodyFinalizer.cpp.obj
│   │   │       │   ├── FunctionDiscoveryAnalyzer.cpp.obj
│   │   │       │   ├── FunctionDiscoveryAnalyzerAdapter.cpp.obj
│   │   │       │   ├── FunctionFingerprint.cpp.obj
│   │   │       │   ├── FunctionStartAnalyzer.cpp.obj
│   │   │       │   ├── FunctionStartDataPostAnalyzer.cpp.obj
│   │   │       │   ├── FunctionStartFuncAnalyzer.cpp.obj
│   │   │       │   ├── FunctionStartPostAnalyzer.cpp.obj
│   │   │       │   ├── FunctionStartPreFuncAnalyzer.cpp.obj
│   │   │       │   ├── GccExceptionAnalyzer.cpp.obj
│   │   │       │   ├── GnuDemanglerAnalyzer.cpp.obj
│   │   │       │   ├── GoBuildInfoParser.cpp.obj
│   │   │       │   ├── GolangStringAnalyzer.cpp.obj
│   │   │       │   ├── GolangSymbolAnalyzer.cpp.obj
│   │   │       │   ├── GoRttiParser.cpp.obj
│   │   │       │   ├── GuardCfgAnalyzer.cpp.obj
│   │   │       │   ├── HCS12ConventionAnalyzer.cpp.obj
│   │   │       │   ├── HexagonAnalyzer.cpp.obj
│   │   │       │   ├── HexagonPrologEpilogAnalyzer.cpp.obj
│   │   │       │   ├── HexagonThunkAnalyzer.cpp.obj
│   │   │       │   ├── HexagonUnsupportSemanticAnalyzer.cpp.obj
│   │   │       │   ├── iBootImAnalyzer.cpp.obj
│   │   │       │   ├── Img2Analyzer.cpp.obj
│   │   │       │   ├── Img3Analyzer.cpp.obj
│   │   │       │   ├── ImportThunkAnalyzer.cpp.obj
│   │   │       │   ├── iOS_Analyzer.cpp.obj
│   │   │       │   ├── iOS_FixupArmSymbolsAnalyzer.cpp.obj
│   │   │       │   ├── iOS_KextStubFixupAnalyzer.cpp.obj
│   │   │       │   ├── JavaAnalyzer.cpp.obj
│   │   │       │   ├── JvmSwitchAnalyzer.cpp.obj
│   │   │       │   ├── KnownFunctionHashes.cpp.obj
│   │   │       │   ├── LinuxTypeDatabase.cpp.obj
│   │   │       │   ├── LoongsonAnalyzer.cpp.obj
│   │   │       │   ├── LzssAnalyzer.cpp.obj
│   │   │       │   ├── MachoAnalyzer.cpp.obj
│   │   │       │   ├── MachoConstructorDestructorAnalyzer.cpp.obj
│   │   │       │   ├── MachoFunctionStartsAnalyzer.cpp.obj
│   │   │       │   ├── MacOSTypeDatabase.cpp.obj
│   │   │       │   ├── MainRecognitionAnalyzer.cpp.obj
│   │   │       │   ├── Memory.cpp.obj
│   │   │       │   ├── MemoryBlock.cpp.obj
│   │   │       │   ├── MemoryByteProvider.cpp.obj
│   │   │       │   ├── MicrosoftDemanglerAnalyzer.cpp.obj
│   │   │       │   ├── MingwRelocationAnalyzer.cpp.obj
│   │   │       │   ├── MipsAddressAnalyzer.cpp.obj
│   │   │       │   ├── MipsPreAnalyzer.cpp.obj
│   │   │       │   ├── MipsSymbolAnalyzer.cpp.obj
│   │   │       │   ├── Motorola68KAnalyzer.cpp.obj
│   │   │       │   ├── Msg.cpp.obj
│   │   │       │   ├── MsvcDemangler.cpp.obj
│   │   │       │   ├── MySwitchAnalyzer.cpp.obj
│   │   │       │   ├── NamingService.cpp.obj
│   │   │       │   ├── NDS32Analyzer.cpp.obj
│   │   │       │   ├── NewExt4Analyzer.cpp.obj
│   │   │       │   ├── NoReturnFunctionAnalyzer.cpp.obj
│   │   │       │   ├── OatExecAnalyzer.cpp.obj
│   │   │       │   ├── OatHeaderAnalyzer.cpp.obj
│   │   │       │   ├── ObjcMessageAnalyzer.cpp.obj
│   │   │       │   ├── ObjcTypeMetadataAnalyzer.cpp.obj
│   │   │       │   ├── OdexHeaderFormatAnalyzer.cpp.obj
│   │   │       │   ├── OperandReferenceAnalyzer.cpp.obj
│   │   │       │   ├── PdbAnalyzer.cpp.obj
│   │   │       │   ├── PdbParser.cpp.obj
│   │   │       │   ├── PdbUniversalAnalyzer.cpp.obj
│   │   │       │   ├── PEExceptionAnalyzer.cpp.obj
│   │   │       │   ├── PefAnalyzer.cpp.obj
│   │   │       │   ├── PefDebugAnalyzer.cpp.obj
│   │   │       │   ├── Pic12Analyzer.cpp.obj
│   │   │       │   ├── Pic16Analyzer.cpp.obj
│   │   │       │   ├── Pic17c7xxAnalyzer.cpp.obj
│   │   │       │   ├── Pic18Analyzer.cpp.obj
│   │   │       │   ├── Pic24DInitAnalyzer.cpp.obj
│   │   │       │   ├── PicSwitchAnalyzer.cpp.obj
│   │   │       │   ├── PortableExecutableAnalyzer.cpp.obj
│   │   │       │   ├── PowerPCAddressAnalyzer.cpp.obj
│   │   │       │   ├── Program.cpp.obj
│   │   │       │   ├── PropagateExternalParametersAnalyzer.cpp.obj
│   │   │       │   ├── RefType.cpp.obj
│   │   │       │   ├── Register.cpp.obj
│   │   │       │   ├── RegisterBuilder.cpp.obj
│   │   │       │   ├── RegisterValue.cpp.obj
│   │   │       │   ├── RISCVAddressAnalyzer.cpp.obj
│   │   │       │   ├── RttiAnalyzer.cpp.obj
│   │   │       │   ├── RustDemanglerAnalyzer.cpp.obj
│   │   │       │   ├── RustStringAnalyzer.cpp.obj
│   │   │       │   ├── ScalarOperandAnalyzer.cpp.obj
│   │   │       │   ├── SegmentedCallingConventionAnalyzer.cpp.obj
│   │   │       │   ├── SH4AddressAnalyzer.cpp.obj
│   │   │       │   ├── SH4EarlyAddressAnalyzer.cpp.obj
│   │   │       │   ├── SharedReturnAnalyzer.cpp.obj
│   │   │       │   ├── SharedReturnJumpAnalyzer.cpp.obj
│   │   │       │   ├── SparcAnalyzer.cpp.obj
│   │   │       │   ├── SparcEarlyAddressAnalyzer.cpp.obj
│   │   │       │   ├── StackFrameImpl.cpp.obj
│   │   │       │   ├── StackReferenceAnalyzer.cpp.obj
│   │   │       │   ├── StackReferenceImpl.cpp.obj
│   │   │       │   ├── StackVariableAnalyzer.cpp.obj
│   │   │       │   ├── StringsAnalyzer.cpp.obj
│   │   │       │   ├── SwiftDemanglerAnalyzer.cpp.obj
│   │   │       │   ├── SwiftTypeMetadataAnalyzer.cpp.obj
│   │   │       │   ├── SymbolicPropogator.cpp.obj
│   │   │       │   ├── TaskMonitor.cpp.obj
│   │   │       │   ├── TEBAnalyzer.cpp.obj
│   │   │       │   ├── ToyAnalyzer.cpp.obj
│   │   │       │   ├── TrackedRegisterSeeder.cpp.obj
│   │   │       │   ├── TypeDatabaseFactory.cpp.obj
│   │   │       │   ├── VarnodeContext.cpp.obj
│   │   │       │   ├── VdexHeaderAnalyzer.cpp.obj
│   │   │       │   ├── WindowsResourceReferenceAnalyzer.cpp.obj
│   │   │       │   ├── WindowsTypeDatabase.cpp.obj
│   │   │       │   ├── X86Analyzer.cpp.obj
│   │   │       │   └── X86FunctionPurgeAnalyzer.cpp.obj
│   │   │       ├── correlate
│   │   │       │   ├── AllBytesHashCalculator.cpp.obj
│   │   │       │   ├── Block.cpp.obj
│   │   │       │   ├── DisambiguateByBytes.cpp.obj
│   │   │       │   ├── DisambiguateByChild.cpp.obj
│   │   │       │   ├── DisambiguateByParent.cpp.obj
│   │   │       │   ├── DisambiguateByParentWithOrder.cpp.obj
│   │   │       │   ├── HashedFunctionAddressCorrelation.cpp.obj
│   │   │       │   ├── HashEntry.cpp.obj
│   │   │       │   ├── HashStore.cpp.obj
│   │   │       │   ├── InstructHash.cpp.obj
│   │   │       │   ├── MnemonicHashCalculator.cpp.obj
│   │   │       │   └── SimpleCRC32.cpp.obj
│   │   │       ├── data
│   │   │       │   ├── AlignedComponentPacker.cpp.obj
│   │   │       │   ├── AlignedStructureInspector.cpp.obj
│   │   │       │   ├── AlignedStructurePacker.cpp.obj
│   │   │       │   ├── AnnotationHandler.cpp.obj
│   │   │       │   ├── BuiltInDataTypeClassExclusionFilter.cpp.obj
│   │   │       │   ├── CompositeInternal.cpp.obj
│   │   │       │   ├── CycleGroup.cpp.obj
│   │   │       │   ├── DataTypeConflictHandler.cpp.obj
│   │   │       │   ├── DataTypeManagerChangeListenerHandler.cpp.obj
│   │   │       │   ├── DataTypeMerger.cpp.obj
│   │   │       │   ├── DataTypeWriter.cpp.obj
│   │   │       │   ├── DefaultAnnotationHandler.cpp.obj
│   │   │       │   ├── InternalDataTypeComponent.cpp.obj
│   │   │       │   └── NoisyStructureBuilder.cpp.obj
│   │   │       ├── decompiler
│   │   │       │   └── CFormatter.cpp.obj
│   │   │       ├── exceptions
│   │   │       │   └── VersionException.cpp.obj
│   │   │       ├── function
│   │   │       │   ├── Function.cpp.obj
│   │   │       │   ├── FunctionManager.cpp.obj
│   │   │       │   └── Variable.cpp.obj
│   │   │       ├── gclass
│   │   │       │   ├── ClassID.cpp.obj
│   │   │       │   └── ClassUtils.cpp.obj
│   │   │       ├── import
│   │   │       │   ├── GbfReader.cpp.obj
│   │   │       │   ├── GzfProgramImporter.cpp.obj
│   │   │       │   ├── RepProject.cpp.obj
│   │   │       │   └── ZipArchive.cpp.obj
│   │   │       ├── lang
│   │   │       │   ├── BasicCompilerSpec.cpp.obj
│   │   │       │   ├── GhidraLanguagePropertyKeys.cpp.obj
│   │   │       │   ├── InjectContext.cpp.obj
│   │   │       │   ├── InjectPayloadSubtypes.cpp.obj
│   │   │       │   ├── InstructionError.cpp.obj
│   │   │       │   ├── InvalidPrototype.cpp.obj
│   │   │       │   ├── MaskImpl.cpp.obj
│   │   │       │   ├── OldLanguageMappingService.cpp.obj
│   │   │       │   └── PrototypeModelMerged.cpp.obj
│   │   │       ├── listing
│   │   │       │   ├── CodeUnit.cpp.obj
│   │   │       │   ├── CommentHistory.cpp.obj
│   │   │       │   ├── Data.cpp.obj
│   │   │       │   ├── DataIterator.cpp.obj
│   │   │       │   ├── DataStub.cpp.obj
│   │   │       │   ├── Instruction.cpp.obj
│   │   │       │   ├── InstructionStub.cpp.obj
│   │   │       │   ├── Library.cpp.obj
│   │   │       │   ├── Listing.cpp.obj
│   │   │       │   ├── StackVariableComparator.cpp.obj
│   │   │       │   ├── StubListing.cpp.obj
│   │   │       │   └── VariableFilter.cpp.obj
│   │   │       ├── marshal
│   │   │       │   ├── XmlDecode.cpp.obj
│   │   │       │   └── XmlEncode.cpp.obj
│   │   │       ├── mem
│   │   │       │   ├── MemoryBlockStub.cpp.obj
│   │   │       │   └── StubMemory.cpp.obj
│   │   │       ├── memory
│   │   │       │   ├── ByteMemBufferImpl.cpp.obj
│   │   │       │   ├── DataConverter.cpp.obj
│   │   │       │   ├── DumbMemBufferImpl.cpp.obj
│   │   │       │   ├── GhidraDataConverter.cpp.obj
│   │   │       │   ├── MemBufferInputStream.cpp.obj
│   │   │       │   ├── MemoryBufferImpl.cpp.obj
│   │   │       │   └── WrappedMemBuffer.cpp.obj
│   │   │       ├── pcode
│   │   │       │   ├── pcode
│   │   │       │   ├── Action.cpp.obj
│   │   │       │   ├── ActionManager.cpp.obj
│   │   │       │   ├── AddrSpace.cpp.obj
│   │   │       │   ├── AndFilter.cpp.obj
│   │   │       │   ├── Architecture.cpp.obj
│   │   │       │   ├── AssignAction.cpp.obj
│   │   │       │   ├── AttributeId.cpp.obj
│   │   │       │   ├── BlockGraph.cpp.obj
│   │   │       │   ├── ByteIngest.cpp.obj
│   │   │       │   ├── CachedEncoder.cpp.obj
│   │   │       │   ├── CodeBlockImpl.cpp.obj
│   │   │       │   ├── CodeBlockReferenceImpl.cpp.obj
│   │   │       │   ├── Comment.cpp.obj
│   │   │       │   ├── ConstructState.cpp.obj
│   │   │       │   ├── ConsumeAs.cpp.obj
│   │   │       │   ├── ConsumeExtra.cpp.obj
│   │   │       │   ├── ConsumeRemaining.cpp.obj
│   │   │       │   ├── ContextDatabase.cpp.obj
│   │   │       │   ├── ContextSetting.cpp.obj
│   │   │       │   ├── ConvertToPointer.cpp.obj
│   │   │       │   ├── Cover.cpp.obj
│   │   │       │   ├── Database.cpp.obj
│   │   │       │   ├── DatatypeFilter.cpp.obj
│   │   │       │   ├── DatatypeMatchFilter.cpp.obj
│   │   │       │   ├── DynamicEntry.cpp.obj
│   │   │       │   ├── DynamicHash.cpp.obj
│   │   │       │   ├── ElementId.cpp.obj
│   │   │       │   ├── Emulate.cpp.obj
│   │   │       │   ├── EnigmaPipeline.cpp.obj
│   │   │       │   ├── ExtCodeBlockImpl.cpp.obj
│   │   │       │   ├── ExtraStack.cpp.obj
│   │   │       │   ├── FloatFormat.cpp.obj
│   │   │       │   ├── FlowInfo.cpp.obj
│   │   │       │   ├── FlowOverride.cpp.obj
│   │   │       │   ├── FuncCallSpecs.cpp.obj
│   │   │       │   ├── Funcdata.cpp.obj
│   │   │       │   ├── GlobalContext.cpp.obj
│   │   │       │   ├── GlobalSymbolMap.cpp.obj
│   │   │       │   ├── GotoStack.cpp.obj
│   │   │       │   ├── Heritage.cpp.obj
│   │   │       │   ├── HiddenReturnAssign.cpp.obj
│   │   │       │   ├── HighFunction.cpp.obj
│   │   │       │   ├── HighSymbol.cpp.obj
│   │   │       │   ├── HighVariable.cpp.obj
│   │   │       │   ├── HomogeneousAggregate.cpp.obj
│   │   │       │   ├── InstructionPcodeOverride.cpp.obj
│   │   │       │   ├── JumpTable.cpp.obj
│   │   │       │   ├── LinkedByteBuffer.cpp.obj
│   │   │       │   ├── LoadImage.cpp.obj
│   │   │       │   ├── LocalSymbolMap.cpp.obj
│   │   │       │   ├── MappedDataEntry.cpp.obj
│   │   │       │   ├── MappedEntry.cpp.obj
│   │   │       │   ├── MetaTypeFilter.cpp.obj
│   │   │       │   ├── ModelRule.cpp.obj
│   │   │       │   ├── MultiMemberAssign.cpp.obj
│   │   │       │   ├── MultiSlotAssign.cpp.obj
│   │   │       │   ├── MultiSlotDualAssign.cpp.obj
│   │   │       │   ├── OpCode.cpp.obj
│   │   │       │   ├── Options.cpp.obj
│   │   │       │   ├── PackedBytes.cpp.obj
│   │   │       │   ├── PackedDecode.cpp.obj
│   │   │       │   ├── PackedDecodeOverlay.cpp.obj
│   │   │       │   ├── PackedEncode.cpp.obj
│   │   │       │   ├── PackedEncodeOverlay.cpp.obj
│   │   │       │   ├── ParamListImpl.cpp.obj
│   │   │       │   ├── ParamListRegisterOut.cpp.obj
│   │   │       │   ├── ParamListStandard.cpp.obj
│   │   │       │   ├── ParamListStandardOut.cpp.obj
│   │   │       │   ├── PatchEncoder.cpp.obj
│   │   │       │   ├── PatchPackedEncode.cpp.obj
│   │   │       │   ├── PcodeBlockBasic.cpp.obj
│   │   │       │   ├── PcodeCapstoneMapper.cpp.obj
│   │   │       │   ├── PcodeInject.cpp.obj
│   │   │       │   ├── PcodeInjectLibrary.cpp.obj
│   │   │       │   ├── PcodeOp.cpp.obj
│   │   │       │   ├── PcodeOpAST.cpp.obj
│   │   │       │   ├── PcodeOpBank.cpp.obj
│   │   │       │   ├── PcodeParser.cpp.obj
│   │   │       │   ├── PcodeSyntaxTree.cpp.obj
│   │   │       │   ├── PositionMatchFilter.cpp.obj
│   │   │       │   ├── PrimitiveExtractor.cpp.obj
│   │   │       │   ├── PrintC.cpp.obj
│   │   │       │   ├── PrintJava.cpp.obj
│   │   │       │   ├── PrintLanguage.cpp.obj
│   │   │       │   ├── QualifierFilter.cpp.obj
│   │   │       │   ├── RegisterManager.cpp.obj
│   │   │       │   ├── RegisterTranslator.cpp.obj
│   │   │       │   ├── RegisterTree.cpp.obj
│   │   │       │   ├── Rule.cpp.obj
│   │   │       │   ├── Scope.cpp.obj
│   │   │       │   ├── SequenceNumber.cpp.obj
│   │   │       │   ├── SizeRestrictedFilter.cpp.obj
│   │   │       │   ├── Sleigh.cpp.obj
│   │   │       │   ├── SleighLanguage.cpp.obj
│   │   │       │   ├── SleighLanguageDescription.cpp.obj
│   │   │       │   ├── SleighLanguageProvider.cpp.obj
│   │   │       │   ├── StringIngest.cpp.obj
│   │   │       │   ├── StructuredBlock.cpp.obj
│   │   │       │   ├── SymbolEntry.cpp.obj
│   │   │       │   ├── Translate.cpp.obj
│   │   │       │   ├── TypeFactory.cpp.obj
│   │   │       │   ├── TypePropagation.cpp.obj
│   │   │       │   ├── UnionFacetSymbol.cpp.obj
│   │   │       │   ├── UniqueLayout.cpp.obj
│   │   │       │   ├── UseropSymbol.cpp.obj
│   │   │       │   ├── VarargsFilter.cpp.obj
│   │   │       │   ├── Varnode.cpp.obj
│   │   │       │   ├── VarnodeAST.cpp.obj
│   │   │       │   ├── VarnodeBank.cpp.obj
│   │   │       │   └── VarnodeTranslator.cpp.obj
│   │   │       ├── program
│   │   │       │   ├── AutoParameterImpl.cpp.obj
│   │   │       │   ├── BookmarkManagerImpl.cpp.obj
│   │   │       │   ├── CodeManager.cpp.obj
│   │   │       │   ├── DatabaseAdapter.cpp.obj
│   │   │       │   ├── DataTypeArchiveImpl.cpp.obj
│   │   │       │   ├── DataTypeManagerImpl.cpp.obj
│   │   │       │   ├── DisassemblerContextAdapter.cpp.obj
│   │   │       │   ├── DynamicVariableStorage.cpp.obj
│   │   │       │   ├── EquateTableImpl.cpp.obj
│   │   │       │   ├── ExternalManagerImpl.cpp.obj
│   │   │       │   ├── FragmentDB.cpp.obj
│   │   │       │   ├── FunctionTagImpl.cpp.obj
│   │   │       │   ├── FunctionTagManagerImpl.cpp.obj
│   │   │       │   ├── InstructionBlock.cpp.obj
│   │   │       │   ├── InstructionBlockFlow.cpp.obj
│   │   │       │   ├── InstructionSet.cpp.obj
│   │   │       │   ├── LocalVariableImpl.cpp.obj
│   │   │       │   ├── ModuleDB.cpp.obj
│   │   │       │   ├── ModuleManager.cpp.obj
│   │   │       │   ├── NamespaceManager.cpp.obj
│   │   │       │   ├── ParameterImpl.cpp.obj
│   │   │       │   ├── ProcessorContextImpl.cpp.obj
│   │   │       │   ├── ProgramAddressFactory.cpp.obj
│   │   │       │   ├── ProgramChangeSet.cpp.obj
│   │   │       │   ├── ProgramContextImpl.cpp.obj
│   │   │       │   ├── ProgramDB.cpp.obj
│   │   │       │   ├── ProgramProcessorContext.cpp.obj
│   │   │       │   ├── PropertyMapManagerImpl.cpp.obj
│   │   │       │   ├── ReadOnlyProcessorContext.cpp.obj
│   │   │       │   ├── ReferenceManagerImpl.cpp.obj
│   │   │       │   ├── RelocationTableImpl.cpp.obj
│   │   │       │   ├── ReturnParameterImpl.cpp.obj
│   │   │       │   ├── SourceFileManagerImpl.cpp.obj
│   │   │       │   ├── SymbolManager.cpp.obj
│   │   │       │   ├── TreeManager.cpp.obj
│   │   │       │   ├── VariableImpl.cpp.obj
│   │   │       │   ├── VariableStorage.cpp.obj
│   │   │       │   └── VariableUtilities.cpp.obj
│   │   │       ├── reloc
│   │   │       │   ├── RelocationResult.cpp.obj
│   │   │       │   └── RelocationUtil.cpp.obj
│   │   │       ├── settings
│   │   │       │   ├── AddressSpaceSettingsDefinition.cpp.obj
│   │   │       │   ├── ComponentOffsetSettingsDefinition.cpp.obj
│   │   │       │   ├── DataTypeMnemonicSettingsDefinition.cpp.obj
│   │   │       │   ├── EndianSettingsDefinition.cpp.obj
│   │   │       │   ├── FloatingPointPrecisionSettingsDefinition.cpp.obj
│   │   │       │   ├── FormatSettingsDefinition.cpp.obj
│   │   │       │   ├── IntegerSignednessFormattingModeSettingsDefinition.cpp.obj
│   │   │       │   ├── MutabilitySettingsDefinition.cpp.obj
│   │   │       │   ├── NumberSettingsDefinition.cpp.obj
│   │   │       │   ├── OffsetMaskSettingsDefinition.cpp.obj
│   │   │       │   ├── OffsetShiftSettingsDefinition.cpp.obj
│   │   │       │   ├── PaddingSettingsDefinition.cpp.obj
│   │   │       │   ├── PointerTypeSettingsDefinition.cpp.obj
│   │   │       │   ├── RGB16EncodingSettingsDefinition.cpp.obj
│   │   │       │   ├── RGB32EncodingSettingsDefinition.cpp.obj
│   │   │       │   ├── SettingsDefinition.cpp.obj
│   │   │       │   ├── SettingsImpl.cpp.obj
│   │   │       │   └── TerminatedSettingsDefinition.cpp.obj
│   │   │       ├── sourcemap
│   │   │       │   ├── DummySourceFileManager.cpp.obj
│   │   │       │   └── SourcePathTransformRecord.cpp.obj
│   │   │       ├── storage
│   │   │       │   ├── BranchManager.cpp.obj
│   │   │       │   ├── CommitManager.cpp.obj
│   │   │       │   ├── Event.cpp.obj
│   │   │       │   ├── EventLog.cpp.obj
│   │   │       │   ├── FksIndexManager.cpp.obj
│   │   │       │   ├── FksRepository.cpp.obj
│   │   │       │   ├── IndexManager.cpp.obj
│   │   │       │   ├── Repository.cpp.obj
│   │   │       │   ├── SnapshotReader.cpp.obj
│   │   │       │   ├── SnapshotWriter.cpp.obj
│   │   │       │   └── WorkingSnapshot.cpp.obj
│   │   │       ├── symbol
│   │   │       │   ├── CodeUnit.cpp.obj
│   │   │       │   ├── ExternalLocation.cpp.obj
│   │   │       │   ├── ExternalLocationAdapter.cpp.obj
│   │   │       │   ├── ExternalPath.cpp.obj
│   │   │       │   ├── Function.cpp.obj
│   │   │       │   ├── FunctionIterator.cpp.obj
│   │   │       │   ├── FunctionSignatureImpl.cpp.obj
│   │   │       │   ├── IllegalCharCppTransformer.cpp.obj
│   │   │       │   ├── Instruction.cpp.obj
│   │   │       │   ├── LabelHistory.cpp.obj
│   │   │       │   ├── Listing.cpp.obj
│   │   │       │   ├── MemReferenceImpl.cpp.obj
│   │   │       │   ├── Namespace.cpp.obj
│   │   │       │   ├── PrototypeModel.cpp.obj
│   │   │       │   ├── Reference.cpp.obj
│   │   │       │   ├── ReferenceIteratorAdapter.cpp.obj
│   │   │       │   ├── RefTypeFactory.cpp.obj
│   │   │       │   ├── SourceFile.cpp.obj
│   │   │       │   ├── Symbol.cpp.obj
│   │   │       │   ├── SymbolIterator.cpp.obj
│   │   │       │   ├── SymbolIteratorAdapter.cpp.obj
│   │   │       │   ├── SymbolTable.cpp.obj
│   │   │       │   ├── SymbolUtilities.cpp.obj
│   │   │       │   ├── ThunkReference.cpp.obj
│   │   │       │   └── Variable.cpp.obj
│   │   │       ├── types
│   │   │       │   ├── AbstractColorDataType.cpp.obj
│   │   │       │   ├── AbstractComplexDataType.cpp.obj
│   │   │       │   ├── AbstractFloatDataType.cpp.obj
│   │   │       │   ├── AbstractIntegerDataType.cpp.obj
│   │   │       │   ├── AbstractLeb128DataType.cpp.obj
│   │   │       │   ├── AbstractPointerTypedefBuiltIn.cpp.obj
│   │   │       │   ├── AbstractSignedIntegerDataType.cpp.obj
│   │   │       │   ├── AbstractStringDataType.cpp.obj
│   │   │       │   ├── AbstractUnsignedIntegerDataType.cpp.obj
│   │   │       │   ├── AIFFDataType.cpp.obj
│   │   │       │   ├── AlignmentDataType.cpp.obj
│   │   │       │   ├── AlignmentType.cpp.obj
│   │   │       │   ├── ArrayDataType.cpp.obj
│   │   │       │   ├── ArrayStringable.cpp.obj
│   │   │       │   ├── AUDataType.cpp.obj
│   │   │       │   ├── AudioPlayer.cpp.obj
│   │   │       │   ├── BadDataType.cpp.obj
│   │   │       │   ├── BitFieldDataType.cpp.obj
│   │   │       │   ├── BitFieldPackingImpl.cpp.obj
│   │   │       │   ├── BitmapResource.cpp.obj
│   │   │       │   ├── BitmapResourceDataType.cpp.obj
│   │   │       │   ├── BooleanDataType.cpp.obj
│   │   │       │   ├── BuiltIn.cpp.obj
│   │   │       │   ├── BuiltInDataTypeManager.cpp.obj
│   │   │       │   ├── ByteDataType.cpp.obj
│   │   │       │   ├── CharDataType.cpp.obj
│   │   │       │   ├── CharsetSettingsDefinition.cpp.obj
│   │   │       │   ├── ColorIcon.cpp.obj
│   │   │       │   ├── Complex16DataType.cpp.obj
│   │   │       │   ├── Complex32DataType.cpp.obj
│   │   │       │   ├── Complex8DataType.cpp.obj
│   │   │       │   ├── Composite.cpp.obj
│   │   │       │   ├── CompositeAlignmentHelper.cpp.obj
│   │   │       │   ├── CompositeDataTypeImpl.cpp.obj
│   │   │       │   ├── CountedDynamicDataType.cpp.obj
│   │   │       │   ├── CustomFormat.cpp.obj
│   │   │       │   ├── DataImage.cpp.obj
│   │   │       │   ├── DataTypeArchiveIdDumper.cpp.obj
│   │   │       │   ├── DataTypeComparator.cpp.obj
│   │   │       │   ├── DataTypeComponentImpl.cpp.obj
│   │   │       │   ├── DataTypeDisplayOptions.cpp.obj
│   │   │       │   ├── DataTypeImpl.cpp.obj
│   │   │       │   ├── DataTypeInstance.cpp.obj
│   │   │       │   ├── DataTypeManagerDomainObject.cpp.obj
│   │   │       │   ├── DataTypeNameComparator.cpp.obj
│   │   │       │   ├── DataTypeObjectComparator.cpp.obj
│   │   │       │   ├── DataTypePath.cpp.obj
│   │   │       │   ├── DataTypeSymbol.cpp.obj
│   │   │       │   ├── DataTypeUtilities.cpp.obj
│   │   │       │   ├── DataTypeWithCharset.cpp.obj
│   │   │       │   ├── DataUtilities.cpp.obj
│   │   │       │   ├── DefaultDataType.cpp.obj
│   │   │       │   ├── DialogResourceDataType.cpp.obj
│   │   │       │   ├── DoubleComplexDataType.cpp.obj
│   │   │       │   ├── DoubleDataType.cpp.obj
│   │   │       │   ├── DWordDataType.cpp.obj
│   │   │       │   ├── DynamicDataType.cpp.obj
│   │   │       │   ├── EnumDataType.cpp.obj
│   │   │       │   ├── FactoryStructureDataType.cpp.obj
│   │   │       │   ├── FileArchiveBasedDataTypeManager.cpp.obj
│   │   │       │   ├── FileDataTypeManager.cpp.obj
│   │   │       │   ├── FileTimeDataType.cpp.obj
│   │   │       │   ├── Float10DataType.cpp.obj
│   │   │       │   ├── Float16DataType.cpp.obj
│   │   │       │   ├── Float2DataType.cpp.obj
│   │   │       │   ├── Float4DataType.cpp.obj
│   │   │       │   ├── Float8DataType.cpp.obj
│   │   │       │   ├── FloatComplexDataType.cpp.obj
│   │   │       │   ├── FloatDataType.cpp.obj
│   │   │       │   ├── FunctionDefinitionDataType.cpp.obj
│   │   │       │   ├── GenericDataType.cpp.obj
│   │   │       │   ├── GifDataType.cpp.obj
│   │   │       │   ├── GIFResource.cpp.obj
│   │   │       │   ├── IBO32DataType.cpp.obj
│   │   │       │   ├── IBO64DataType.cpp.obj
│   │   │       │   ├── IconMaskResourceDataType.cpp.obj
│   │   │       │   ├── IconResource.cpp.obj
│   │   │       │   ├── IconResourceDataType.cpp.obj
│   │   │       │   ├── IndexedDynamicDataType.cpp.obj
│   │   │       │   ├── Integer16DataType.cpp.obj
│   │   │       │   ├── Integer3DataType.cpp.obj
│   │   │       │   ├── Integer5DataType.cpp.obj
│   │   │       │   ├── Integer6DataType.cpp.obj
│   │   │       │   ├── Integer7DataType.cpp.obj
│   │   │       │   ├── IntegerDataType.cpp.obj
│   │   │       │   ├── JPEGDataType.cpp.obj
│   │   │       │   ├── LongDataType.cpp.obj
│   │   │       │   ├── LongDoubleComplexDataType.cpp.obj
│   │   │       │   ├── LongDoubleDataType.cpp.obj
│   │   │       │   ├── LongLongDataType.cpp.obj
│   │   │       │   ├── MacintoshTimeStampDataType.cpp.obj
│   │   │       │   ├── MemBufferImageInputStream.cpp.obj
│   │   │       │   ├── MenuResourceDataType.cpp.obj
│   │   │       │   ├── MetaDataType.cpp.obj
│   │   │       │   ├── MIDIDataType.cpp.obj
│   │   │       │   ├── MissingBuiltInDataType.cpp.obj
│   │   │       │   ├── OpBehavior.cpp.obj
│   │   │       │   ├── PackingType.cpp.obj
│   │   │       │   ├── ParameterDefinitionImpl.cpp.obj
│   │   │       │   ├── PartialUnion.cpp.obj
│   │   │       │   ├── PascalString255DataType.cpp.obj
│   │   │       │   ├── PascalStringDataType.cpp.obj
│   │   │       │   ├── PascalUnicodeDataType.cpp.obj
│   │   │       │   ├── Playable.cpp.obj
│   │   │       │   ├── PngDataType.cpp.obj
│   │   │       │   ├── PngResource.cpp.obj
│   │   │       │   ├── Pointer16DataType.cpp.obj
│   │   │       │   ├── Pointer24DataType.cpp.obj
│   │   │       │   ├── Pointer32DataType.cpp.obj
│   │   │       │   ├── Pointer40DataType.cpp.obj
│   │   │       │   ├── Pointer48DataType.cpp.obj
│   │   │       │   ├── Pointer56DataType.cpp.obj
│   │   │       │   ├── Pointer64DataType.cpp.obj
│   │   │       │   ├── Pointer8DataType.cpp.obj
│   │   │       │   ├── PointerDataType.cpp.obj
│   │   │       │   ├── PointerTypedef.cpp.obj
│   │   │       │   ├── PointerTypedefBuilder.cpp.obj
│   │   │       │   ├── ProgramArchitectureTranslator.cpp.obj
│   │   │       │   ├── ProjectArchiveBasedDataTypeManager.cpp.obj
│   │   │       │   ├── QWordDataType.cpp.obj
│   │   │       │   ├── ReadOnlyDataTypeComponent.cpp.obj
│   │   │       │   ├── RenderUnicodeSettingsDefinition.cpp.obj
│   │   │       │   ├── RepeatCountDataType.cpp.obj
│   │   │       │   ├── RepeatedDynamicDataType.cpp.obj
│   │   │       │   ├── RepeatedStringDataType.cpp.obj
│   │   │       │   ├── Resource.cpp.obj
│   │   │       │   ├── RGB16ColorDataType.cpp.obj
│   │   │       │   ├── RGB32ColorDataType.cpp.obj
│   │   │       │   ├── ScorePlayer.cpp.obj
│   │   │       │   ├── SegmentedCodePointerDataType.cpp.obj
│   │   │       │   ├── ShiftedAddressDataType.cpp.obj
│   │   │       │   ├── ShortDataType.cpp.obj
│   │   │       │   ├── SignedByteDataType.cpp.obj
│   │   │       │   ├── SignedCharDataType.cpp.obj
│   │   │       │   ├── SignedDWordDataType.cpp.obj
│   │   │       │   ├── SignedLeb128DataType.cpp.obj
│   │   │       │   ├── SignedQWordDataType.cpp.obj
│   │   │       │   ├── SignedWordDataType.cpp.obj
│   │   │       │   ├── SourceArchiveImpl.cpp.obj
│   │   │       │   ├── StandAloneDataTypeManager.cpp.obj
│   │   │       │   ├── StringDataInstance.cpp.obj
│   │   │       │   ├── StringDataType.cpp.obj
│   │   │       │   ├── StringLayoutEnum.cpp.obj
│   │   │       │   ├── StringRenderBuilder.cpp.obj
│   │   │       │   ├── StringRenderParser.cpp.obj
│   │   │       │   ├── StringUTF8DataType.cpp.obj
│   │   │       │   ├── StructureDataType.cpp.obj
│   │   │       │   ├── StructuredDynamicDataType.cpp.obj
│   │   │       │   ├── StructureFactory.cpp.obj
│   │   │       │   ├── TerminatedStringDataType.cpp.obj
│   │   │       │   ├── TerminatedUnicode32DataType.cpp.obj
│   │   │       │   ├── TerminatedUnicodeDataType.cpp.obj
│   │   │       │   ├── TranslationSettingsDefinition.cpp.obj
│   │   │       │   ├── TypedefDataType.cpp.obj
│   │   │       │   ├── Undefined.cpp.obj
│   │   │       │   ├── Undefined1DataType.cpp.obj
│   │   │       │   ├── Undefined2DataType.cpp.obj
│   │   │       │   ├── Undefined3DataType.cpp.obj
│   │   │       │   ├── Undefined4DataType.cpp.obj
│   │   │       │   ├── Undefined5DataType.cpp.obj
│   │   │       │   ├── Undefined6DataType.cpp.obj
│   │   │       │   ├── Undefined7DataType.cpp.obj
│   │   │       │   ├── Undefined8DataType.cpp.obj
│   │   │       │   ├── Unicode32DataType.cpp.obj
│   │   │       │   ├── UnicodeDataType.cpp.obj
│   │   │       │   ├── UnionDataType.cpp.obj
│   │   │       │   ├── UnsignedCharDataType.cpp.obj
│   │   │       │   ├── UnsignedInteger16DataType.cpp.obj
│   │   │       │   ├── UnsignedInteger3DataType.cpp.obj
│   │   │       │   ├── UnsignedInteger5DataType.cpp.obj
│   │   │       │   ├── UnsignedInteger6DataType.cpp.obj
│   │   │       │   ├── UnsignedInteger7DataType.cpp.obj
│   │   │       │   ├── UnsignedIntegerDataType.cpp.obj
│   │   │       │   ├── UnsignedLeb128DataType.cpp.obj
│   │   │       │   ├── UnsignedLongDataType.cpp.obj
│   │   │       │   ├── UnsignedLongLongDataType.cpp.obj
│   │   │       │   ├── UnsignedShortDataType.cpp.obj
│   │   │       │   ├── VoidDataType.cpp.obj
│   │   │       │   ├── WAVEDataType.cpp.obj
│   │   │       │   ├── WideChar16DataType.cpp.obj
│   │   │       │   ├── WideChar32DataType.cpp.obj
│   │   │       │   ├── WideCharDataType.cpp.obj
│   │   │       │   └── WordDataType.cpp.obj
│   │   │       └── util
│   │   │           ├── datastruct
│   │   │           ├── graph
│   │   │           ├── AcyclicCallGraphBuilder.cpp.obj
│   │   │           ├── AndQuery.cpp.obj
│   │   │           ├── CharsetInfo.cpp.obj
│   │   │           ├── CharsetInfoManager.cpp.obj
│   │   │           ├── DefaultIntPropertyMap.cpp.obj
│   │   │           ├── DefaultPropertyMap.cpp.obj
│   │   │           ├── Fixup.cpp.obj
│   │   │           ├── LEB128.cpp.obj
│   │   │           ├── LongIterator.cpp.obj
│   │   │           ├── MemoryByteIterator.cpp.obj
│   │   │           ├── NoSettings.cpp.obj
│   │   │           ├── NumericUtilities.cpp.obj
│   │   │           ├── OrQuery.cpp.obj
│   │   │           ├── ProgramChangeRecord.cpp.obj
│   │   │           ├── PropertySet.cpp.obj
│   │   │           ├── Query.cpp.obj
│   │   │           ├── StringUtilities.cpp.obj
│   │   │           └── SymbolPath.cpp.obj
│   │   ├── enigma_evaluate_cross_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_evaluate_cross.dir
│   │   │   ├── enigma_evaluate_cross_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── evaluate_cross_library.cpp.obj
│   │   ├── enigma_evaluate_graph_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_evaluate_graph.dir
│   │   │   ├── enigma_evaluate_graph_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── evaluate_graph_matching.cpp.obj
│   │   ├── enigma_evaluate_id_rate_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_evaluate_id_rate.dir
│   │   │   ├── enigma_evaluate_id_rate_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── evaluate_id_rate_from_fkslib.cpp.obj
│   │   ├── enigma_final_survey_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_final_survey.dir
│   │   │   ├── enigma_final_survey_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── final_survey.cpp.obj
│   │   ├── enigma_find_no_relations_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_find_no_relations.dir
│   │   │   ├── enigma_find_no_relations_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── find_no_relations.cpp.obj
│   │   ├── enigma_fingerprint_audit_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_fingerprint_audit.dir
│   │   │   ├── enigma_fingerprint_audit_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_fingerprint_audit.cpp.obj
│   │   ├── enigma_fks_build_index_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_fks_build_index.dir
│   │   │   ├── enigma_fks_build_index_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_fks_build_index.cpp.obj
│   │   ├── enigma_fks_export_hashes_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_fks_export_hashes.dir
│   │   │   ├── enigma_fks_export_hashes_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_fks_export_hashes.cpp.obj
│   │   ├── enigma_fks_ingest_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_fks_ingest_from_ghidra_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_fks_ingest_from_ghidra.dir
│   │   │   ├── enigma_fks_ingest_from_ghidra_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_fks_ingest_from_ghidra.cpp.obj
│   │   ├── enigma_fks_ingest.dir
│   │   │   ├── enigma_fks_ingest_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_fks_ingest.cpp.obj
│   │   ├── enigma_gui_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   ├── AutoRcc_resources_MXUWEOXILK_Info.json
│   │   │   ├── AutoRcc_resources_MXUWEOXILK_Lock.lock
│   │   │   ├── AutoRcc_resources_MXUWEOXILK_Used.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_gui.dir
│   │   │   ├── enigma_gui_autogen
│   │   │   │   ├── MXUWEOXILK
│   │   │   │   │   └── qrc_resources.cpp.obj
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── src
│   │   │       └── gui
│   │   │           ├── AddressMinimap.cpp.obj
│   │   │           ├── AsmHighlighter.cpp.obj
│   │   │           ├── CodePlainTextEdit.cpp.obj
│   │   │           ├── CommandPaletteDialog.cpp.obj
│   │   │           ├── ConsoleWidget.cpp.obj
│   │   │           ├── CppHighlighter.cpp.obj
│   │   │           ├── CrossReferenceExplorer.cpp.obj
│   │   │           ├── DecompilerView.cpp.obj
│   │   │           ├── DisasmSearchBar.cpp.obj
│   │   │           ├── DisassemblyFieldView.cpp.obj
│   │   │           ├── DisassemblyModel.cpp.obj
│   │   │           ├── DisassemblyView.cpp.obj
│   │   │           ├── DyldCacheBrowserDialog.cpp.obj
│   │   │           ├── EditorTheme.cpp.obj
│   │   │           ├── FieldView.cpp.obj
│   │   │           ├── FunctionExplorer.cpp.obj
│   │   │           ├── FunctionGraphView.cpp.obj
│   │   │           ├── FunctionGraphWindow.cpp.obj
│   │   │           ├── GuiConflictHandler.cpp.obj
│   │   │           ├── HexSearchBar.cpp.obj
│   │   │           ├── HexView.cpp.obj
│   │   │           ├── main.cpp.obj
│   │   │           ├── MainWindow.cpp.obj
│   │   │           ├── NavigationCoordinator.cpp.obj
│   │   │           ├── PatchListWidget.cpp.obj
│   │   │           ├── SelectionManager.cpp.obj
│   │   │           ├── StatusBarWidget.cpp.obj
│   │   │           ├── StringTableWidget.cpp.obj
│   │   │           ├── StructureEditorWidget.cpp.obj
│   │   │           └── TypeConflictDialog.cpp.obj
│   │   ├── enigma_gzf_inspect_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_gzf_inspect.dir
│   │   │   ├── enigma_gzf_inspect_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_gzf_inspect.cpp.obj
│   │   ├── enigma_gzf_probe_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_gzf_probe.dir
│   │   │   ├── enigma_gzf_probe_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_gzf_probe.cpp.obj
│   │   ├── enigma_list_ghidra_status_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_list_ghidra_status.dir
│   │   │   ├── enigma_list_ghidra_status_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── list_ghidra_status.cpp.obj
│   │   ├── enigma_naming_audit_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_naming_audit.dir
│   │   │   ├── enigma_naming_audit_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_naming_audit.cpp.obj
│   │   ├── enigma_patch_cli_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_patch_cli.dir
│   │   │   ├── enigma_patch_cli_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_patch_cli.cpp.obj
│   │   ├── enigma_pipeline_audit_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_pipeline_audit.dir
│   │   │   ├── enigma_pipeline_audit_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── enigma_pipeline_audit.cpp.obj
│   │   ├── enigma_rebuild_fks_index_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_rebuild_fks_index.dir
│   │   │   ├── enigma_rebuild_fks_index_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── rebuild_fks_index.cpp.obj
│   │   ├── enigma_survey_fkslibs_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_survey_fkslibs.dir
│   │   │   ├── enigma_survey_fkslibs_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── survey_fkslibs.cpp.obj
│   │   ├── enigma_survey_v3_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_survey_v3.dir
│   │   │   ├── enigma_survey_v3_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tools
│   │   │       └── survey_v3_status.cpp.obj
│   │   ├── enigma_test_aarch64_pipeline_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_aarch64_pipeline.dir
│   │   │   ├── enigma_test_aarch64_pipeline_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_aarch64_pipeline.cpp.obj
│   │   ├── enigma_test_analyzer_integration_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_analyzer_integration.dir
│   │   │   ├── enigma_test_analyzer_integration_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_analyzer_integration.cpp.obj
│   │   ├── enigma_test_apply_known_signature_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_apply_known_signature.dir
│   │   │   ├── enigma_test_apply_known_signature_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_apply_known_signature.cpp.obj
│   │   ├── enigma_test_assembler_patching_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_assembler_patching.dir
│   │   │   ├── enigma_test_assembler_patching_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_assembler_patching.cpp.obj
│   │   ├── enigma_test_batch_aa_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_aa.dir
│   │   │   ├── enigma_test_batch_aa_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_aa.cpp.obj
│   │   ├── enigma_test_batch_ab_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_ab.dir
│   │   │   ├── enigma_test_batch_ab_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_ab.cpp.obj
│   │   ├── enigma_test_batch_e_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_e.dir
│   │   │   ├── enigma_test_batch_e_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_e.cpp.obj
│   │   ├── enigma_test_batch_f_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_f.dir
│   │   │   ├── enigma_test_batch_f_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_f.cpp.obj
│   │   ├── enigma_test_batch_g_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_g.dir
│   │   │   ├── enigma_test_batch_g_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_g.cpp.obj
│   │   ├── enigma_test_batch_h_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_h.dir
│   │   │   ├── enigma_test_batch_h_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_h.cpp.obj
│   │   ├── enigma_test_batch_i_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_i.dir
│   │   │   ├── enigma_test_batch_i_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_i.cpp.obj
│   │   ├── enigma_test_batch_j_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_j.dir
│   │   │   ├── enigma_test_batch_j_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_j.cpp.obj
│   │   ├── enigma_test_batch_k_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_k.dir
│   │   │   ├── enigma_test_batch_k_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_k.cpp.obj
│   │   ├── enigma_test_batch_l_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_l.dir
│   │   │   ├── enigma_test_batch_l_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_l.cpp.obj
│   │   ├── enigma_test_batch_n_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_n.dir
│   │   │   ├── enigma_test_batch_n_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_n.cpp.obj
│   │   ├── enigma_test_batch_o_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_o.dir
│   │   │   ├── enigma_test_batch_o_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_o.cpp.obj
│   │   ├── enigma_test_batch_p_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_p.dir
│   │   │   ├── enigma_test_batch_p_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_p.cpp.obj
│   │   ├── enigma_test_batch_q_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_q.dir
│   │   │   ├── enigma_test_batch_q_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_q.cpp.obj
│   │   ├── enigma_test_batch_r_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_r.dir
│   │   │   ├── enigma_test_batch_r_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_r.cpp.obj
│   │   ├── enigma_test_batch_s_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_s.dir
│   │   │   ├── enigma_test_batch_s_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_s.cpp.obj
│   │   ├── enigma_test_batch_t_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_t.dir
│   │   │   ├── enigma_test_batch_t_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_t.cpp.obj
│   │   ├── enigma_test_batch_u_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_u.dir
│   │   │   ├── enigma_test_batch_u_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_u.cpp.obj
│   │   ├── enigma_test_batch_v_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_v.dir
│   │   │   ├── enigma_test_batch_v_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_v.cpp.obj
│   │   ├── enigma_test_batch_w_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_w.dir
│   │   │   ├── enigma_test_batch_w_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_w.cpp.obj
│   │   ├── enigma_test_batch_x_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_x.dir
│   │   │   ├── enigma_test_batch_x_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_x.cpp.obj
│   │   ├── enigma_test_batch_y_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_y.dir
│   │   │   ├── enigma_test_batch_y_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_y.cpp.obj
│   │   ├── enigma_test_batch_z_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_batch_z.dir
│   │   │   ├── enigma_test_batch_z_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_batch_z.cpp.obj
│   │   ├── enigma_test_block_struct_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_block_struct.dir
│   │   │   ├── enigma_test_block_struct_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_block_struct.cpp.obj
│   │   ├── enigma_test_coff_loader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_coff_loader.dir
│   │   │   ├── enigma_test_coff_loader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_coff_loader.cpp.obj
│   │   ├── enigma_test_compile_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_compile.dir
│   │   │   ├── enigma_test_compile_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_compile.cpp.obj
│   │   ├── enigma_test_datatype_merger_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_datatype_merger.dir
│   │   │   ├── enigma_test_datatype_merger_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_datatype_merger.cpp.obj
│   │   ├── enigma_test_decomp_interface_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_decomp_interface.dir
│   │   │   ├── enigma_test_decomp_interface_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_decomp_interface.cpp.obj
│   │   ├── enigma_test_decompiler_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_decompiler.dir
│   │   │   ├── enigma_test_decompiler_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_decompiler.cpp.obj
│   │   ├── enigma_test_disasm_cfg_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_disasm_cfg.dir
│   │   │   ├── enigma_test_disasm_cfg_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_disasm_cfg.cpp.obj
│   │   ├── enigma_test_elf_compiler_detect_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_elf_compiler_detect.dir
│   │   │   ├── enigma_test_elf_compiler_detect_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_elf_compiler_detect.cpp.obj
│   │   ├── enigma_test_elf_dyn_overlap_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_elf_dyn_overlap.dir
│   │   │   ├── enigma_test_elf_dyn_overlap_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_elf_dyn_overlap.cpp.obj
│   │   ├── enigma_test_elf_pltgot_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_elf_pltgot.dir
│   │   │   ├── enigma_test_elf_pltgot_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_elf_pltgot.cpp.obj
│   │   ├── enigma_test_firmware_loader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_firmware_loader.dir
│   │   │   ├── enigma_test_firmware_loader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_firmware_loader.cpp.obj
│   │   ├── enigma_test_fks_fingerprint_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_fks_fingerprint.dir
│   │   │   ├── enigma_test_fks_fingerprint_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_fks_fingerprint.cpp.obj
│   │   ├── enigma_test_fks_index_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_fks_index.dir
│   │   │   ├── enigma_test_fks_index_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_fks_index.cpp.obj
│   │   ├── enigma_test_fks_library_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_fks_library.dir
│   │   │   ├── enigma_test_fks_library_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_fks_library.cpp.obj
│   │   ├── enigma_test_function_boundaries_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_function_boundaries.dir
│   │   │   ├── enigma_test_function_boundaries_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_function_boundaries.cpp.obj
│   │   ├── enigma_test_function_graph_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_function_graph.dir
│   │   │   ├── enigma_test_function_graph_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_function_graph.cpp.obj
│   │   ├── enigma_test_gap_verification_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gap_verification.dir
│   │   │   ├── enigma_test_gap_verification_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gap_verification.cpp.obj
│   │   ├── enigma_test_gbf_reader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gbf_reader.dir
│   │   │   ├── enigma_test_gbf_reader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gbf_reader.cpp.obj
│   │   ├── enigma_test_gnu_build_attributes_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gnu_build_attributes.dir
│   │   │   ├── enigma_test_gnu_build_attributes_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gnu_build_attributes.cpp.obj
│   │   ├── enigma_test_golang_pipeline_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_golang_pipeline.dir
│   │   │   ├── enigma_test_golang_pipeline_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_golang_pipeline.cpp.obj
│   │   ├── enigma_test_gui_smoke_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gui_smoke.dir
│   │   │   ├── enigma_test_gui_smoke_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   ├── src
│   │   │   │   └── gui
│   │   │   │       ├── DyldCacheBrowserDialog.cpp.obj
│   │   │   │       └── FunctionExplorer.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gui_smoke.cpp.obj
│   │   ├── enigma_test_gzf_equates_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gzf_equates.dir
│   │   │   ├── enigma_test_gzf_equates_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gzf_equates.cpp.obj
│   │   ├── enigma_test_gzf_fidelity_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gzf_fidelity.dir
│   │   │   ├── enigma_test_gzf_fidelity_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gzf_fidelity.cpp.obj
│   │   ├── enigma_test_gzf_function_tags_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gzf_function_tags.dir
│   │   │   ├── enigma_test_gzf_function_tags_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gzf_function_tags.cpp.obj
│   │   ├── enigma_test_gzf_import_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gzf_import.dir
│   │   │   ├── enigma_test_gzf_import_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gzf_import.cpp.obj
│   │   ├── enigma_test_gzf_rebase_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_gzf_rebase.dir
│   │   │   ├── enigma_test_gzf_rebase_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_gzf_rebase.cpp.obj
│   │   ├── enigma_test_headless_suite_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_headless_suite.dir
│   │   │   ├── enigma_test_headless_suite_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_headless_suite.cpp.obj
│   │   ├── enigma_test_lang_classes_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_lang_classes.dir
│   │   │   ├── enigma_test_lang_classes_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_lang_classes.cpp.obj
│   │   ├── enigma_test_loader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_loader.dir
│   │   │   ├── enigma_test_loader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_loader.cpp.obj
│   │   ├── enigma_test_macho_loader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_macho_loader.dir
│   │   │   ├── enigma_test_macho_loader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_macho_loader.cpp.obj
│   │   ├── enigma_test_mips16_context_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_mips16_context.dir
│   │   │   ├── enigma_test_mips16_context_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_mips16_context.cpp.obj
│   │   ├── enigma_test_objc_backend_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_objc_backend.dir
│   │   │   ├── enigma_test_objc_backend_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_objc_backend.cpp.obj
│   │   ├── enigma_test_patching_features_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_patching_features.dir
│   │   │   ├── enigma_test_patching_features_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_patching_features.cpp.obj
│   │   ├── enigma_test_pdb_parser_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_pdb_parser.dir
│   │   │   ├── enigma_test_pdb_parser_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_pdb_parser.cpp.obj
│   │   ├── enigma_test_pe_loader_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_pe_loader.dir
│   │   │   ├── enigma_test_pe_loader_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_pe_loader.cpp.obj
│   │   ├── enigma_test_pipeline_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_pipeline_comprehensive_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_pipeline_comprehensive.dir
│   │   │   ├── enigma_test_pipeline_comprehensive_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_pipeline_comprehensive.cpp.obj
│   │   ├── enigma_test_pipeline.dir
│   │   │   ├── enigma_test_pipeline_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_pipeline.cpp.obj
│   │   ├── enigma_test_repository_reload_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_repository_reload.dir
│   │   │   ├── enigma_test_repository_reload_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_repository_reload.cpp.obj
│   │   ├── enigma_test_rust_strings_backend_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_rust_strings_backend.dir
│   │   │   ├── enigma_test_rust_strings_backend_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_rust_strings_backend.cpp.obj
│   │   ├── enigma_test_signature_persistence_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_signature_persistence.dir
│   │   │   ├── enigma_test_signature_persistence_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_signature_persistence.cpp.obj
│   │   ├── enigma_test_storage_p1_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_storage_p1.dir
│   │   │   ├── enigma_test_storage_p1_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_storage_phase1.cpp.obj
│   │   ├── enigma_test_storage_p2_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_storage_p2.dir
│   │   │   ├── enigma_test_storage_p2_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_storage_phase2.cpp.obj
│   │   ├── enigma_test_storage_p3_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_storage_p3.dir
│   │   │   ├── enigma_test_storage_p3_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_storage_phase3.cpp.obj
│   │   ├── enigma_test_storage_p4_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_storage_p4.dir
│   │   │   ├── enigma_test_storage_p4_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_storage_phase4.cpp.obj
│   │   ├── enigma_test_storage_p5_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_storage_p5.dir
│   │   │   ├── enigma_test_storage_p5_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_storage_phase5.cpp.obj
│   │   ├── enigma_test_stress_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_stress.dir
│   │   │   ├── enigma_test_stress_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_decompiler_stress.cpp.obj
│   │   ├── enigma_test_swift_backend_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_swift_backend.dir
│   │   │   ├── enigma_test_swift_backend_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_swift_backend.cpp.obj
│   │   ├── enigma_test_type_roundtrip_autogen.dir
│   │   │   ├── AutogenInfo.json
│   │   │   ├── AutogenUsed.txt
│   │   │   └── ParseCache.txt
│   │   ├── enigma_test_type_roundtrip.dir
│   │   │   ├── enigma_test_type_roundtrip_autogen
│   │   │   │   └── mocs_compilation.cpp.obj
│   │   │   └── tests
│   │   │       └── test_type_roundtrip.cpp.obj
│   │   ├── pkgRedirects
│   │   ├── clean_additional.cmake
│   │   ├── cmake.check_cache
│   │   ├── cmake.verify_globs
│   │   ├── CMakeConfigureLog.yaml
│   │   ├── InstallScripts.json
│   │   ├── rules.ninja
│   │   ├── TargetDirectories.txt
│   │   └── VerifyGlobs.cmake
│   ├── corpus_src
│   │   ├── arm32_fib.c
│   │   ├── arm32_fib.elf
│   │   ├── mipsel_fib.elf
│   │   └── ppc32_fib.elf
│   ├── enigma_binary_audit_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_decompile_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_decompile_full_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_dump_functions_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_dump_listing_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_evaluate_cross_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_evaluate_graph_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_evaluate_id_rate_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_final_survey_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_find_no_relations_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_fingerprint_audit_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_fks_build_index_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_fks_export_hashes_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_fks_ingest_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_fks_ingest_from_ghidra_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_gui_autogen
│   │   ├── include
│   │   ├── MXUWEOXILK
│   │   │   ├── moc_AddressMinimap.cpp
│   │   │   ├── moc_AddressMinimap.cpp.d
│   │   │   ├── moc_CodePlainTextEdit.cpp
│   │   │   ├── moc_CodePlainTextEdit.cpp.d
│   │   │   ├── moc_CommandPaletteDialog.cpp
│   │   │   ├── moc_CommandPaletteDialog.cpp.d
│   │   │   ├── moc_ConsoleWidget.cpp
│   │   │   ├── moc_ConsoleWidget.cpp.d
│   │   │   ├── moc_CppHighlighter.cpp
│   │   │   ├── moc_CppHighlighter.cpp.d
│   │   │   ├── moc_CrossReferenceExplorer.cpp
│   │   │   ├── moc_CrossReferenceExplorer.cpp.d
│   │   │   ├── moc_DecompilerView.cpp
│   │   │   ├── moc_DecompilerView.cpp.d
│   │   │   ├── moc_DisasmSearchBar.cpp
│   │   │   ├── moc_DisasmSearchBar.cpp.d
│   │   │   ├── moc_DisassemblyFieldView.cpp
│   │   │   ├── moc_DisassemblyFieldView.cpp.d
│   │   │   ├── moc_DyldCacheBrowserDialog.cpp
│   │   │   ├── moc_DyldCacheBrowserDialog.cpp.d
│   │   │   ├── moc_FieldView.cpp
│   │   │   ├── moc_FieldView.cpp.d
│   │   │   ├── moc_FunctionExplorer.cpp
│   │   │   ├── moc_FunctionExplorer.cpp.d
│   │   │   ├── moc_FunctionGraphView.cpp
│   │   │   ├── moc_FunctionGraphView.cpp.d
│   │   │   ├── moc_FunctionGraphWindow.cpp
│   │   │   ├── moc_FunctionGraphWindow.cpp.d
│   │   │   ├── moc_HexSearchBar.cpp
│   │   │   ├── moc_HexSearchBar.cpp.d
│   │   │   ├── moc_HexView.cpp
│   │   │   ├── moc_HexView.cpp.d
│   │   │   ├── moc_MainWindow.cpp
│   │   │   ├── moc_MainWindow.cpp.d
│   │   │   ├── moc_PatchListWidget.cpp
│   │   │   ├── moc_PatchListWidget.cpp.d
│   │   │   ├── moc_SelectionManager.cpp
│   │   │   ├── moc_SelectionManager.cpp.d
│   │   │   ├── moc_StatusBarWidget.cpp
│   │   │   ├── moc_StatusBarWidget.cpp.d
│   │   │   ├── moc_StringTableWidget.cpp
│   │   │   ├── moc_StringTableWidget.cpp.d
│   │   │   ├── moc_StructureEditorWidget.cpp
│   │   │   ├── moc_StructureEditorWidget.cpp.d
│   │   │   ├── moc_TypeConflictDialog.cpp
│   │   │   ├── moc_TypeConflictDialog.cpp.d
│   │   │   └── qrc_resources.cpp
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_gzf_inspect_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_gzf_probe_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_list_ghidra_status_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_naming_audit_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_patch_cli_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_pipeline_audit_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_rebuild_fks_index_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_survey_fkslibs_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_survey_v3_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_aarch64_pipeline_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_analyzer_integration_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_apply_known_signature_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_assembler_patching_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_aa_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_ab_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_e_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_f_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_g_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_h_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_i_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_j_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_k_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_l_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_n_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_o_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_p_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_q_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_r_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_s_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_t_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_u_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_v_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_w_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_x_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_y_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_batch_z_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_block_struct_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_coff_loader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_compile_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_datatype_merger_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_decomp_interface_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_decompiler_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_disasm_cfg_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_elf_compiler_detect_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_elf_dyn_overlap_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_elf_pltgot_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_firmware_loader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_fks_fingerprint_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_fks_index_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_fks_library_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_function_boundaries_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_function_graph_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gap_verification_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gbf_reader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gnu_build_attributes_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_golang_pipeline_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gui_smoke_autogen
│   │   ├── include
│   │   ├── MXUWEOXILK
│   │   │   ├── moc_DyldCacheBrowserDialog.cpp
│   │   │   ├── moc_DyldCacheBrowserDialog.cpp.d
│   │   │   ├── moc_FunctionExplorer.cpp
│   │   │   └── moc_FunctionExplorer.cpp.d
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gzf_equates_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gzf_fidelity_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gzf_function_tags_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gzf_import_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_gzf_rebase_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_headless_suite_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_lang_classes_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_loader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_macho_loader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_mips16_context_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_objc_backend_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_patching_features_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_pdb_parser_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_pe_loader_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_pipeline_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_pipeline_comprehensive_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_repository_reload_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_rust_strings_backend_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_signature_persistence_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_storage_p1_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_storage_p2_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_storage_p3_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_storage_p4_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_storage_p5_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_stress_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_swift_backend_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── enigma_test_type_roundtrip_autogen
│   │   ├── include
│   │   ├── deps
│   │   ├── moc_predefs.h
│   │   ├── mocs_compilation.cpp
│   │   └── timestamp
│   ├── repo_fidelity_key_1a00aef16a2
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00aef16a4
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_key_1a00afa1c61
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00afa1c64
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_key_1a00afb3f27
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00afb3f2a
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_key_1a00b098a93
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00b098a97
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_key_1a00b09b5a0
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00b09b5a1
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00ae386a2
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00ae386a6
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00ae3b734
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00ae3b736
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00ae6c7d7
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00ae6c7db
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00d61a16b
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00d61a173
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00d6220cc
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00d6220d2
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_fidelity_notepad_1a00d625121
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a00d62512d
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_reload_1a008f912b0
│   │   ├── binary
│   │   ├── commits
│   │   │   ├── 1a008f912b7
│   │   │   │   ├── changeset.fbs
│   │   │   │   ├── commit.meta
│   │   │   │   └── snapshot.fbs
│   │   │   ├── 1a008f912be
│   │   │   │   ├── changeset.fbs
│   │   │   │   ├── commit.meta
│   │   │   │   └── snapshot.fbs
│   │   │   └── 1a008f912c1
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_reload_1a008f9b8db
│   │   ├── binary
│   │   ├── commits
│   │   │   ├── 1a008f9b8df
│   │   │   │   ├── changeset.fbs
│   │   │   │   ├── commit.meta
│   │   │   │   └── snapshot.fbs
│   │   │   ├── 1a008f9b8e4
│   │   │   │   ├── changeset.fbs
│   │   │   │   ├── commit.meta
│   │   │   │   └── snapshot.fbs
│   │   │   └── 1a008f9b8e8
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_sig_verify_1a008f91033
│   │   ├── binary
│   │   ├── commits
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_type_1a008f91574
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a008f91579
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── repo_type_1a008f9bb21
│   │   ├── binary
│   │   ├── commits
│   │   │   └── 1a008f9bb26
│   │   │       ├── changeset.fbs
│   │   │       ├── commit.meta
│   │   │       └── snapshot.fbs
│   │   ├── index
│   │   │   └── lmdb
│   │   ├── metadata
│   │   │   └── project.meta
│   │   └── working
│   ├── schemas
│   │   ├── changeset_generated.h
│   │   ├── commit_generated.h
│   │   ├── fks_generated.h
│   │   ├── program_generated.h
│   │   └── project_generated.h
│   ├── Testing
│   │   └── Temporary
│   │       ├── CTestCostData.txt
│   │       ├── LastTest.log.tmp3706d
│   │       ├── LastTest.log.tmp378f3
│   │       ├── LastTest.log.tmp3b023
│   │       ├── LastTest.log.tmp8177e
│   │       ├── LastTest.log.tmp8255d
│   │       ├── LastTest.log.tmp8a2dc
│   │       ├── LastTest.log.tmp976dd
│   │       ├── LastTest.log.tmp9ab9f
│   │       ├── LastTest.log.tmpc90fc
│   │       └── LastTestsFailed.log.tmpebe09
│   ├── build.ninja
│   ├── cmake_install.cmake
│   ├── CMakeCache.txt
│   ├── CTestTestfile.cmake
│   ├── enigma_binary_audit.exe
│   ├── enigma_decompile_full.exe
│   ├── enigma_decompile.exe
│   ├── enigma_dump_functions.exe
│   ├── enigma_dump_listing.exe
│   ├── enigma_evaluate_cross.exe
│   ├── enigma_evaluate_graph.exe
│   ├── enigma_evaluate_id_rate.exe
│   ├── enigma_final_survey.exe
│   ├── enigma_find_no_relations.exe
│   ├── enigma_fingerprint_audit.exe
│   ├── enigma_fks_build_index.exe
│   ├── enigma_fks_export_hashes.exe
│   ├── enigma_fks_ingest_from_ghidra.exe
│   ├── enigma_fks_ingest.exe
│   ├── enigma_gui.exe
│   ├── enigma_gzf_inspect.exe
│   ├── enigma_gzf_probe.exe
│   ├── enigma_list_ghidra_status.exe
│   ├── enigma_naming_audit.exe
│   ├── enigma_patch_cli.exe
│   ├── enigma_pipeline_audit.exe
│   ├── enigma_rebuild_fks_index.exe
│   ├── enigma_survey_fkslibs.exe
│   ├── enigma_survey_v3.exe
│   ├── enigma_test_aarch64_pipeline.exe
│   ├── enigma_test_analyzer_integration.exe
│   ├── enigma_test_apply_known_signature.exe
│   ├── enigma_test_assembler_patching.exe
│   ├── enigma_test_batch_aa.exe
│   ├── enigma_test_batch_ab.exe
│   ├── enigma_test_batch_e.exe
│   ├── enigma_test_batch_f.exe
│   ├── enigma_test_batch_g.exe
│   ├── enigma_test_batch_h.exe
│   ├── enigma_test_batch_i.exe
│   ├── enigma_test_batch_j.exe
│   ├── enigma_test_batch_k.exe
│   ├── enigma_test_batch_l.exe
│   ├── enigma_test_batch_n.exe
│   ├── enigma_test_batch_o.exe
│   ├── enigma_test_batch_p.exe
│   ├── enigma_test_batch_q.exe
│   ├── enigma_test_batch_r.exe
│   ├── enigma_test_batch_s.exe
│   ├── enigma_test_batch_t.exe
│   ├── enigma_test_batch_u.exe
│   ├── enigma_test_batch_v.exe
│   ├── enigma_test_batch_w.exe
│   ├── enigma_test_batch_x.exe
│   ├── enigma_test_batch_y.exe
│   ├── enigma_test_batch_z.exe
│   ├── enigma_test_block_struct.exe
│   ├── enigma_test_coff_loader.exe
│   ├── enigma_test_compile.exe
│   ├── enigma_test_datatype_merger.exe
│   ├── enigma_test_decomp_interface.exe
│   ├── enigma_test_decompiler.exe
│   ├── enigma_test_disasm_cfg.exe
│   ├── enigma_test_elf_compiler_detect.exe
│   ├── enigma_test_elf_dyn_overlap.exe
│   ├── enigma_test_elf_pltgot.exe
│   ├── enigma_test_firmware_loader.exe
│   ├── enigma_test_fks_fingerprint.exe
│   ├── enigma_test_fks_index.exe
│   ├── enigma_test_fks_library.exe
│   ├── enigma_test_function_boundaries.exe
│   ├── enigma_test_function_graph.exe
│   ├── enigma_test_gap_verification.exe
│   ├── enigma_test_gbf_reader.exe
│   ├── enigma_test_gnu_build_attributes.exe
│   ├── enigma_test_golang_pipeline.exe
│   ├── enigma_test_gui_smoke.exe
│   ├── enigma_test_gzf_equates.exe
│   ├── enigma_test_gzf_fidelity.exe
│   ├── enigma_test_gzf_function_tags.exe
│   ├── enigma_test_gzf_import.exe
│   ├── enigma_test_gzf_rebase.exe
│   ├── enigma_test_headless_suite.exe
│   ├── enigma_test_lang_classes.exe
│   ├── enigma_test_loader.exe
│   ├── enigma_test_macho_loader.exe
│   ├── enigma_test_mips16_context.exe
│   ├── enigma_test_objc_backend.exe
│   ├── enigma_test_patching_features.exe
│   ├── enigma_test_pdb_parser.exe
│   ├── enigma_test_pe_loader.exe
│   ├── enigma_test_pipeline_comprehensive.exe
│   ├── enigma_test_pipeline.exe
│   ├── enigma_test_repository_reload.exe
│   ├── enigma_test_rust_strings_backend.exe
│   ├── enigma_test_signature_persistence.exe
│   ├── enigma_test_storage_p1.exe
│   ├── enigma_test_storage_p2.exe
│   ├── enigma_test_storage_p3.exe
│   ├── enigma_test_storage_p4.exe
│   ├── enigma_test_storage_p5.exe
│   ├── enigma_test_stress.exe
│   ├── enigma_test_swift_backend.exe
│   ├── enigma_test_type_roundtrip.exe
│   ├── libdecompiler.a
│   ├── libenigma_engine.a
│   └── stGdCC9m
├── build_asan
│   ├── CMakeFiles
│   │   ├── 4.3.2
│   │   │   ├── CompilerIdC
│   │   │   │   ├── tmp
│   │   │   │   ├── a.exe
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   ├── CompilerIdCXX
│   │   │   │   ├── tmp
│   │   │   │   ├── CMakeCXXCompilerId.cpp
│   │   │   │   └── CMakeCXXCompilerId.o
│   │   │   ├── CMakeRCCompiler.cmake
│   │   │   └── CMakeSystem.cmake
│   │   ├── CMakeScratch
│   │   ├── pkgRedirects
│   │   ├── cmake.check_cache
│   │   └── CMakeConfigureLog.yaml
│   └── CMakeCache.txt
├── dist
│   ├── platforms
│   │   └── qwindows.dll
│   ├── sleigh
│   │   ├── 6502
│   │   │   ├── 6502.cspec
│   │   │   ├── 6502.ldefs
│   │   │   ├── 6502.pspec
│   │   │   ├── 6502.sla
│   │   │   ├── 6502.slaspec
│   │   │   ├── 65c02.sla
│   │   │   └── 65c02.slaspec
│   │   ├── 68000
│   │   │   ├── 68000_register.cspec
│   │   │   ├── 68000.cspec
│   │   │   ├── 68000.ldefs
│   │   │   ├── 68000.pspec
│   │   │   ├── 68020.sla
│   │   │   ├── 68020.slaspec
│   │   │   ├── 68030.sla
│   │   │   ├── 68030.slaspec
│   │   │   ├── 68040.sla
│   │   │   ├── 68040.slaspec
│   │   │   ├── coldfire.sla
│   │   │   └── coldfire.slaspec
│   │   ├── 8048
│   │   │   ├── 8048.cspec
│   │   │   ├── 8048.ldefs
│   │   │   ├── 8048.pspec
│   │   │   ├── 8048.sla
│   │   │   └── 8048.slaspec
│   │   ├── 8051
│   │   │   ├── 80251.cspec
│   │   │   ├── 80251.pspec
│   │   │   ├── 80251.sla
│   │   │   ├── 80251.slaspec
│   │   │   ├── 80390.cspec
│   │   │   ├── 80390.sla
│   │   │   ├── 80390.slaspec
│   │   │   ├── 8051_archimedes.cspec
│   │   │   ├── 8051.cspec
│   │   │   ├── 8051.ldefs
│   │   │   ├── 8051.pspec
│   │   │   ├── 8051.sla
│   │   │   ├── 8051.slaspec
│   │   │   ├── cip-51.sla
│   │   │   ├── cip-51.slaspec
│   │   │   ├── keil-cx51.cspec
│   │   │   ├── mx51.cspec
│   │   │   ├── mx51.pspec
│   │   │   ├── mx51.sla
│   │   │   └── mx51.slaspec
│   │   ├── AARCH64
│   │   │   ├── AARCH64_apple.cspec
│   │   │   ├── AARCH64_AppleSilicon.sla
│   │   │   ├── AARCH64_AppleSilicon.slaspec
│   │   │   ├── AARCH64_golang.cspec
│   │   │   ├── AARCH64_ilp32.cspec
│   │   │   ├── AARCH64_swift.cspec
│   │   │   ├── AARCH64_win.cspec
│   │   │   ├── AARCH64.cspec
│   │   │   ├── AARCH64.ldefs
│   │   │   ├── AARCH64.pspec
│   │   │   ├── AARCH64.sla
│   │   │   ├── AARCH64.slaspec
│   │   │   ├── AARCH64BE.sla
│   │   │   ├── AARCH64BE.slaspec
│   │   │   └── AppleSilicon.ldefs
│   │   ├── ARM
│   │   │   ├── ARM_apcs.cspec
│   │   │   ├── ARM_v45.cspec
│   │   │   ├── ARM_v45.pspec
│   │   │   ├── ARM_win.cspec
│   │   │   ├── ARM.cspec
│   │   │   ├── ARM.ldefs
│   │   │   ├── ARM4_be.sla
│   │   │   ├── ARM4_be.slaspec
│   │   │   ├── ARM4_le.sla
│   │   │   ├── ARM4_le.slaspec
│   │   │   ├── ARM4t_be.sla
│   │   │   ├── ARM4t_be.slaspec
│   │   │   ├── ARM4t_le.sla
│   │   │   ├── ARM4t_le.slaspec
│   │   │   ├── ARM5_be.sla
│   │   │   ├── ARM5_be.slaspec
│   │   │   ├── ARM5_le.sla
│   │   │   ├── ARM5_le.slaspec
│   │   │   ├── ARM5t_be.sla
│   │   │   ├── ARM5t_be.slaspec
│   │   │   ├── ARM5t_le.sla
│   │   │   ├── ARM5t_le.slaspec
│   │   │   ├── ARM6_be.sla
│   │   │   ├── ARM6_be.slaspec
│   │   │   ├── ARM6_le.sla
│   │   │   ├── ARM6_le.slaspec
│   │   │   ├── ARM7_be.sla
│   │   │   ├── ARM7_be.slaspec
│   │   │   ├── ARM7_le.sla
│   │   │   ├── ARM7_le.slaspec
│   │   │   ├── ARM8_be.sla
│   │   │   ├── ARM8_be.slaspec
│   │   │   ├── ARM8_le.sla
│   │   │   ├── ARM8_le.slaspec
│   │   │   ├── ARM8m_be.sla
│   │   │   ├── ARM8m_be.slaspec
│   │   │   ├── ARM8m_le.sla
│   │   │   ├── ARM8m_le.slaspec
│   │   │   ├── ARMCortex.pspec
│   │   │   ├── ARMt_v45.pspec
│   │   │   ├── ARMt_v6.pspec
│   │   │   ├── ARMt.pspec
│   │   │   └── ARMtTHUMB.pspec
│   │   ├── BPF
│   │   │   ├── BPF_le.sla
│   │   │   ├── BPF_le.slaspec
│   │   │   ├── BPF.cspec
│   │   │   ├── BPF.ldefs
│   │   │   └── BPF.pspec
│   │   ├── Dalvik
│   │   │   ├── Dalvik_Base.cspec
│   │   │   ├── Dalvik_Base.pspec
│   │   │   ├── Dalvik_Base.sla
│   │   │   ├── Dalvik_Base.slaspec
│   │   │   ├── Dalvik_DEX_Android10.sla
│   │   │   ├── Dalvik_DEX_Android10.slaspec
│   │   │   ├── Dalvik_DEX_Android11.sla
│   │   │   ├── Dalvik_DEX_Android11.slaspec
│   │   │   ├── Dalvik_DEX_Android12.sla
│   │   │   ├── Dalvik_DEX_Android12.slaspec
│   │   │   ├── Dalvik_DEX_KitKat.sla
│   │   │   ├── Dalvik_DEX_KitKat.slaspec
│   │   │   ├── Dalvik_DEX_Lollipop.sla
│   │   │   ├── Dalvik_DEX_Lollipop.slaspec
│   │   │   ├── Dalvik_DEX_Marshmallow.sla
│   │   │   ├── Dalvik_DEX_Marshmallow.slaspec
│   │   │   ├── Dalvik_DEX_Nougat.sla
│   │   │   ├── Dalvik_DEX_Nougat.slaspec
│   │   │   ├── Dalvik_DEX_Oreo.sla
│   │   │   ├── Dalvik_DEX_Oreo.slaspec
│   │   │   ├── Dalvik_DEX_Pie.sla
│   │   │   ├── Dalvik_DEX_Pie.slaspec
│   │   │   ├── Dalvik_ODEX_KitKat.sla
│   │   │   ├── Dalvik_ODEX_KitKat.slaspec
│   │   │   └── Dalvik.ldefs
│   │   ├── eBPF
│   │   │   ├── eBPF_be.sla
│   │   │   ├── eBPF_be.slaspec
│   │   │   ├── eBPF_le.sla
│   │   │   ├── eBPF_le.slaspec
│   │   │   ├── eBPF.cspec
│   │   │   ├── eBPF.ldefs
│   │   │   └── eBPF.pspec
│   │   ├── Hexagon
│   │   │   ├── hexagon.cspec
│   │   │   ├── hexagon.ldefs
│   │   │   ├── hexagon.pspec
│   │   │   ├── hexagon.sla
│   │   │   └── hexagon.slaspec
│   │   ├── JVM
│   │   │   ├── JVM.cspec
│   │   │   ├── JVM.ldefs
│   │   │   ├── JVM.pspec
│   │   │   ├── JVM.sla
│   │   │   └── JVM.slaspec
│   │   ├── Loongarch
│   │   │   ├── ilp32d.cspec
│   │   │   ├── ilp32f.cspec
│   │   │   ├── loongarch.ldefs
│   │   │   ├── loongarch32_f32.sla
│   │   │   ├── loongarch32_f32.slaspec
│   │   │   ├── loongarch32_f64.sla
│   │   │   ├── loongarch32_f64.slaspec
│   │   │   ├── loongarch32.pspec
│   │   │   ├── loongarch64_f32.sla
│   │   │   ├── loongarch64_f32.slaspec
│   │   │   ├── loongarch64_f64.sla
│   │   │   ├── loongarch64_f64.slaspec
│   │   │   ├── loongarch64.pspec
│   │   │   ├── lp64d.cspec
│   │   │   └── lp64f.cspec
│   │   ├── MIPS
│   │   │   ├── mips.ldefs
│   │   │   ├── mips32_eabi.cspec
│   │   │   ├── mips32_fp64.cspec
│   │   │   ├── mips32.pspec
│   │   │   ├── mips32be.cspec
│   │   │   ├── mips32be.sla
│   │   │   ├── mips32be.slaspec
│   │   │   ├── mips32le.cspec
│   │   │   ├── mips32le.sla
│   │   │   ├── mips32le.slaspec
│   │   │   ├── mips32micro.pspec
│   │   │   ├── mips32R6.pspec
│   │   │   ├── mips32R6be.sla
│   │   │   ├── mips32R6be.slaspec
│   │   │   ├── mips32R6le.sla
│   │   │   ├── mips32R6le.slaspec
│   │   │   ├── mips64_32_n32.cspec
│   │   │   ├── mips64_32_o32.cspec
│   │   │   ├── mips64_32_o64.cspec
│   │   │   ├── mips64.pspec
│   │   │   ├── mips64be.cspec
│   │   │   ├── mips64be.sla
│   │   │   ├── mips64be.slaspec
│   │   │   ├── mips64le.cspec
│   │   │   ├── mips64le.sla
│   │   │   ├── mips64le.slaspec
│   │   │   ├── mips64micro.pspec
│   │   │   └── mips64R6.pspec
│   │   ├── NDS32
│   │   │   ├── nds32.cspec
│   │   │   ├── nds32.ldefs
│   │   │   ├── nds32.pspec
│   │   │   ├── nds32be.sla
│   │   │   ├── nds32be.slaspec
│   │   │   ├── nds32le.sla
│   │   │   └── nds32le.slaspec
│   │   ├── PA-RISC
│   │   │   ├── pa-risc.ldefs
│   │   │   ├── pa-risc32.cspec
│   │   │   ├── pa-risc32.pspec
│   │   │   ├── pa-risc32be.sla
│   │   │   └── pa-risc32be.slaspec
│   │   ├── PIC
│   │   │   ├── dsPIC30F.sla
│   │   │   ├── dsPIC30F.slaspec
│   │   │   ├── dsPIC33C.sla
│   │   │   ├── dsPIC33C.slaspec
│   │   │   ├── dsPIC33E.sla
│   │   │   ├── dsPIC33E.slaspec
│   │   │   ├── dsPIC33F.sla
│   │   │   ├── dsPIC33F.slaspec
│   │   │   ├── pic12c5xx.cspec
│   │   │   ├── pic12c5xx.ldefs
│   │   │   ├── pic12c5xx.pspec
│   │   │   ├── pic12c5xx.sla
│   │   │   ├── pic12c5xx.slaspec
│   │   │   ├── pic16.cspec
│   │   │   ├── pic16.ldefs
│   │   │   ├── pic16.pspec
│   │   │   ├── pic16.sla
│   │   │   ├── pic16.slaspec
│   │   │   ├── pic16c5x.cspec
│   │   │   ├── pic16c5x.ldefs
│   │   │   ├── pic16c5x.pspec
│   │   │   ├── pic16c5x.sla
│   │   │   ├── pic16c5x.slaspec
│   │   │   ├── pic16f.cspec
│   │   │   ├── pic16f.pspec
│   │   │   ├── pic16f.sla
│   │   │   ├── pic16f.slaspec
│   │   │   ├── pic17c7xx.cspec
│   │   │   ├── pic17c7xx.ldefs
│   │   │   ├── pic17c7xx.pspec
│   │   │   ├── pic17c7xx.sla
│   │   │   ├── pic17c7xx.slaspec
│   │   │   ├── pic18.cspec
│   │   │   ├── pic18.ldefs
│   │   │   ├── pic18.pspec
│   │   │   ├── pic18.sla
│   │   │   ├── pic18.slaspec
│   │   │   ├── PIC24.cspec
│   │   │   ├── PIC24.ldefs
│   │   │   ├── PIC24.pspec
│   │   │   ├── PIC24E.sla
│   │   │   ├── PIC24E.slaspec
│   │   │   ├── PIC24F.sla
│   │   │   ├── PIC24F.slaspec
│   │   │   ├── PIC24H.sla
│   │   │   └── PIC24H.slaspec
│   │   ├── PowerPC
│   │   │   ├── ppc_32_4xx_be.sla
│   │   │   ├── ppc_32_4xx_be.slaspec
│   │   │   ├── ppc_32_4xx_le.sla
│   │   │   ├── ppc_32_4xx_le.slaspec
│   │   │   ├── ppc_32_be_Mac.cspec
│   │   │   ├── ppc_32_be.sla
│   │   │   ├── ppc_32_be.slaspec
│   │   │   ├── ppc_32_e500_be.cspec
│   │   │   ├── ppc_32_e500_be.sla
│   │   │   ├── ppc_32_e500_be.slaspec
│   │   │   ├── ppc_32_e500_le.cspec
│   │   │   ├── ppc_32_e500_le.sla
│   │   │   ├── ppc_32_e500_le.slaspec
│   │   │   ├── ppc_32_e500mc_be.cspec
│   │   │   ├── ppc_32_e500mc_be.sla
│   │   │   ├── ppc_32_e500mc_be.slaspec
│   │   │   ├── ppc_32_e500mc_le.cspec
│   │   │   ├── ppc_32_e500mc_le.sla
│   │   │   ├── ppc_32_e500mc_le.slaspec
│   │   │   ├── ppc_32_le.sla
│   │   │   ├── ppc_32_le.slaspec
│   │   │   ├── ppc_32_mpc8270.pspec
│   │   │   ├── ppc_32_quicciii_be.sla
│   │   │   ├── ppc_32_quicciii_be.slaspec
│   │   │   ├── ppc_32_quicciii_le.sla
│   │   │   ├── ppc_32_quicciii_le.slaspec
│   │   │   ├── ppc_32.cspec
│   │   │   ├── ppc_32.pspec
│   │   │   ├── ppc_64_32.cspec
│   │   │   ├── ppc_64_be_Mac.cspec
│   │   │   ├── ppc_64_be.cspec
│   │   │   ├── ppc_64_be.sla
│   │   │   ├── ppc_64_be.slaspec
│   │   │   ├── ppc_64_isa_altivec_be.sla
│   │   │   ├── ppc_64_isa_altivec_be.slaspec
│   │   │   ├── ppc_64_isa_altivec_le.sla
│   │   │   ├── ppc_64_isa_altivec_le.slaspec
│   │   │   ├── ppc_64_isa_altivec_vle_be.sla
│   │   │   ├── ppc_64_isa_altivec_vle_be.slaspec
│   │   │   ├── ppc_64_isa_be.sla
│   │   │   ├── ppc_64_isa_be.slaspec
│   │   │   ├── ppc_64_isa_le.sla
│   │   │   ├── ppc_64_isa_le.slaspec
│   │   │   ├── ppc_64_isa_vle_be.sla
│   │   │   ├── ppc_64_isa_vle_be.slaspec
│   │   │   ├── ppc_64_le.cspec
│   │   │   ├── ppc_64_le.sla
│   │   │   ├── ppc_64_le.slaspec
│   │   │   ├── ppc_64.pspec
│   │   │   └── ppc.ldefs
│   │   ├── RISCV
│   │   │   ├── andestar_v5.ldefs
│   │   │   ├── andestar_v5.sla
│   │   │   ├── andestar_v5.slaspec
│   │   │   ├── riscv.ilp32d.sla
│   │   │   ├── riscv.ilp32d.slaspec
│   │   │   ├── riscv.ldefs
│   │   │   ├── riscv.lp64d.sla
│   │   │   ├── riscv.lp64d.slaspec
│   │   │   ├── riscv32-fp.cspec
│   │   │   ├── riscv32.cspec
│   │   │   ├── riscv64-fp.cspec
│   │   │   ├── riscv64.cspec
│   │   │   ├── RV32.pspec
│   │   │   └── RV64.pspec
│   │   ├── Sparc
│   │   │   ├── SparcV9_32.cspec
│   │   │   ├── SparcV9_32.sla
│   │   │   ├── SparcV9_32.slaspec
│   │   │   ├── SparcV9_64.cspec
│   │   │   ├── SparcV9_64.sla
│   │   │   ├── SparcV9_64.slaspec
│   │   │   ├── SparcV9.ldefs
│   │   │   └── SparcV9.pspec
│   │   ├── SuperH
│   │   │   ├── sh-1.sla
│   │   │   ├── sh-1.slaspec
│   │   │   ├── sh-2.sla
│   │   │   ├── sh-2.slaspec
│   │   │   ├── sh-2a.sla
│   │   │   ├── sh-2a.slaspec
│   │   │   ├── superh.cspec
│   │   │   ├── superh.ldefs
│   │   │   ├── superh.pspec
│   │   │   └── superh2a.cspec
│   │   ├── TriCore
│   │   │   ├── tc172x.pspec
│   │   │   ├── tc176x.pspec
│   │   │   ├── tc29x.pspec
│   │   │   ├── tricore.cspec
│   │   │   ├── tricore.ldefs
│   │   │   ├── tricore.pspec
│   │   │   ├── tricore.sla
│   │   │   └── tricore.slaspec
│   │   ├── V850
│   │   │   ├── V850.cspec
│   │   │   ├── V850.ldefs
│   │   │   ├── V850.pspec
│   │   │   ├── V850.sla
│   │   │   └── V850.slaspec
│   │   ├── x86
│   │   │   ├── x86-16-real.pspec
│   │   │   ├── x86-16.cspec
│   │   │   ├── x86-16.pspec
│   │   │   ├── x86-32-golang.cspec
│   │   │   ├── x86-64-compat32.pspec
│   │   │   ├── x86-64-gcc.cspec
│   │   │   ├── x86-64-golang.cspec
│   │   │   ├── x86-64-swift.cspec
│   │   │   ├── x86-64-win.cspec
│   │   │   ├── x86-64.pspec
│   │   │   ├── x86-64.sla
│   │   │   ├── x86-64.slaspec
│   │   │   ├── x86.ldefs
│   │   │   ├── x86.pspec
│   │   │   ├── x86.sla
│   │   │   ├── x86.slaspec
│   │   │   ├── x86borland.cspec
│   │   │   ├── x86delphi.cspec
│   │   │   ├── x86gcc.cspec
│   │   │   └── x86win.cspec
│   │   ├── Xtensa
│   │   │   ├── xtensa_be.sla
│   │   │   ├── xtensa_be.slaspec
│   │   │   ├── xtensa_le.sla
│   │   │   ├── xtensa_le.slaspec
│   │   │   ├── xtensa.cspec
│   │   │   ├── xtensa.ldefs
│   │   │   └── xtensa.pspec
│   │   └── Z80
│   │       ├── z180.pspec
│   │       ├── z180.sla
│   │       ├── z180.slaspec
│   │       ├── z182.pspec
│   │       ├── z80.cspec
│   │       ├── z80.ldefs
│   │       ├── z80.pspec
│   │       ├── z80.sla
│   │       ├── z80.slaspec
│   │       └── z8401x.pspec
│   ├── styles
│   │   └── qmodernwindowsstyle.dll
│   ├── donate.svg
│   ├── enigma_gui.exe
│   ├── enigma_test_patching_features.exe
│   ├── folder-free.png
│   ├── folder-free.png.tmp.png
│   ├── folder-free.svg
│   ├── folder-open.png
│   ├── folder-open.png.tmp.png
│   ├── folder-open.svg
│   ├── help.svg
│   ├── libcapstone.dll
│   ├── libgcc_s_seh-1.dll
│   ├── liblmdb.dll
│   ├── libstdc++-6.dll
│   ├── libwinpthread-1.dll
│   ├── notepad_patched.exe
│   ├── notepad_test.exe
│   ├── Qt6Core.dll
│   ├── Qt6Gui.dll
│   ├── Qt6Svg.dll
│   ├── Qt6Widgets.dll
│   ├── settings.svg
│   └── zlib1.dll
├── fid
│   ├── acspecfc_ghidra.fkslib
│   ├── activeds_ghidra.fkslib
│   ├── adsldp_ghidra.fkslib
│   ├── adsnt_ghidra.fkslib
│   ├── advapi32_arm64_ghidra.fkslib
│   ├── advapi32_ghidra.fkslib
│   ├── apphelp_ghidra.fkslib
│   ├── AppXDeploymentExtensions_onecore_arm64_ghidra.fkslib
│   ├── AppXDeploymentServer_arm64_ghidra.fkslib
│   ├── authfw_ghidra.fkslib
│   ├── AuthFWSnapin_arm64_ghidra.fkslib
│   ├── avifil32_ghidra.fkslib
│   ├── bcryptprimitives_arm64_ghidra.fkslib
│   ├── bcryptprimitives_ghidra.fkslib
│   ├── bfe_ghidra.fkslib
│   ├── BingMaps_arm64_ghidra.fkslib
│   ├── bingmaps_ghidra.fkslib
│   ├── cdp_arm64_ghidra.fkslib
│   ├── cdp_ghidra.fkslib
│   ├── certca_ghidra.fkslib
│   ├── certcli_ghidra.fkslib
│   ├── CertEnroll_arm64_ghidra.fkslib
│   ├── certenroll_ghidra.fkslib
│   ├── cfgmgr32_arm64_ghidra.fkslib
│   ├── cfgmgr32_ghidra.fkslib
│   ├── chakra_arm64_ghidra.fkslib
│   ├── chakra_ghidra.fkslib
│   ├── chakradiag_ghidra.fkslib
│   ├── chakrathunk_ghidra.fkslib
│   ├── clbcatq_ghidra.fkslib
│   ├── clusapi_arm64_ghidra.fkslib
│   ├── clusapi_ghidra.fkslib
│   ├── colbact_ghidra.fkslib
│   ├── combase_arm64_ghidra.fkslib
│   ├── combase_ghidra.fkslib
│   ├── comctl32_arm64_ghidra.fkslib
│   ├── comctl32_ghidra.fkslib
│   ├── comdlg32_arm64_ghidra.fkslib
│   ├── comdlg32_ghidra.fkslib
│   ├── compstui_ghidra.fkslib
│   ├── comsnap_ghidra.fkslib
│   ├── comsvcs_ghidra.fkslib
│   ├── concrt140_arm64_ghidra.fkslib
│   ├── concrt140_ghidra.fkslib
│   ├── CoreUIComponents_arm64_ghidra.fkslib
│   ├── cppdap_ghidra.fkslib
│   ├── credssp_ghidra.fkslib
│   ├── credui_arm64_ghidra.fkslib
│   ├── credui_ghidra.fkslib
│   ├── crypt32_arm64_ghidra.fkslib
│   ├── crypt32_ghidra.fkslib
│   ├── cryptnet_ghidra.fkslib
│   ├── cscapi_ghidra.fkslib
│   ├── cscdll_ghidra.fkslib
│   ├── csrss_ghidra.fkslib
│   ├── d2d1_arm64_ghidra.fkslib
│   ├── d2d1_ghidra.fkslib
│   ├── d3d10warp_arm64_ghidra.fkslib
│   ├── d3d10warp_ghidra.fkslib
│   ├── d3d11_arm64_ghidra.fkslib
│   ├── d3d11_ghidra.fkslib
│   ├── d3d12_arm64_ghidra.fkslib
│   ├── d3d12_ghidra.fkslib
│   ├── d3d12core_arm64_ghidra.fkslib
│   ├── d3d9_arm64_ghidra.fkslib
│   ├── d3d9_ghidra.fkslib
│   ├── d3dcompiler_47_arm64_ghidra.fkslib
│   ├── d3dcsx_42_ghidra.fkslib
│   ├── d3dx9_36_ghidra.fkslib
│   ├── d3dx9_37_ghidra.fkslib
│   ├── d3dx9_38_ghidra.fkslib
│   ├── d3dx9_39_ghidra.fkslib
│   ├── d3dx9_40_ghidra.fkslib
│   ├── d3dx9_41_ghidra.fkslib
│   ├── dbgeng_arm64_ghidra.fkslib
│   ├── dbgeng_ghidra.fkslib
│   ├── dbghelp_arm64_ghidra.fkslib
│   ├── dbghelp_ghidra.fkslib
│   ├── dcomp_arm64_ghidra.fkslib
│   ├── ddraw_ghidra.fkslib
│   ├── devenum_ghidra.fkslib
│   ├── devobj_ghidra.fkslib
│   ├── dhcpcsvc_ghidra.fkslib
│   ├── diagtrack_arm64_ghidra.fkslib
│   ├── dinput8_ghidra.fkslib
│   ├── directml_arm64_arm64_ghidra.fkslib
│   ├── directml_x64_arm64_ghidra.fkslib
│   ├── dispex_ghidra.fkslib
│   ├── dnsapi_arm64_ghidra.fkslib
│   ├── dnsapi_ghidra.fkslib
│   ├── dpapi_ghidra.fkslib
│   ├── dpapisrv_ghidra.fkslib
│   ├── drvstore_ghidra.fkslib
│   ├── dsound_arm64_ghidra.fkslib
│   ├── dsound_ghidra.fkslib
│   ├── dwmapi_arm64_ghidra.fkslib
│   ├── dwmapi_ghidra.fkslib
│   ├── dwrite_arm64_ghidra.fkslib
│   ├── dwrite_ghidra.fkslib
│   ├── dxgi_arm64_ghidra.fkslib
│   ├── dxgi_ghidra.fkslib
│   ├── dxva2_arm64_ghidra.fkslib
│   ├── dxva2_ghidra.fkslib
│   ├── edgeangle_arm64_ghidra.fkslib
│   ├── edgecontent_arm64_ghidra.fkslib
│   ├── edgehtml_arm64_ghidra.fkslib
│   ├── edgehtml_ghidra.fkslib
│   ├── edgemanager_arm64_ghidra.fkslib
│   ├── efslsaext_ghidra.fkslib
│   ├── es_ghidra.fkslib
│   ├── esent_arm64_ghidra.fkslib
│   ├── esent_ghidra.fkslib
│   ├── evr_arm64_ghidra.fkslib
│   ├── evr_ghidra.fkslib
│   ├── ExplorerFrame_arm64_ghidra.fkslib
│   ├── faultrep_arm64_ghidra.fkslib
│   ├── faultrep_ghidra.fkslib
│   ├── fdproxy_ghidra.fkslib
│   ├── fdssdp_ghidra.fkslib
│   ├── fltlib_ghidra.fkslib
│   ├── fwpuclnt_ghidra.fkslib
│   ├── gdi32_arm64_ghidra.fkslib
│   ├── gdi32_ghidra.fkslib
│   ├── gdi32full_arm64_ghidra.fkslib
│   ├── gdi32full_ghidra.fkslib
│   ├── gdiplus_ghidra.fkslib
│   ├── glu32_ghidra.fkslib
│   ├── gnutls30_ghidra.fkslib
│   ├── go_runtime_ghidra.fkslib
│   ├── harfbuzz_subset_ghidra.fkslib
│   ├── hlink_ghidra.fkslib
│   ├── icm32_ghidra.fkslib
│   ├── icu_ghidra.fkslib
│   ├── icudt78_ghidra.fkslib
│   ├── icuin78_ghidra.fkslib
│   ├── icuuc78_ghidra.fkslib
│   ├── ieframe_arm64_ghidra.fkslib
│   ├── ieframe_ghidra.fkslib
│   ├── iertutil_arm64_ghidra.fkslib
│   ├── iertutil_ghidra.fkslib
│   ├── imagehlp_arm64_ghidra.fkslib
│   ├── imagehlp_ghidra.fkslib
│   ├── imm32_arm64_ghidra.fkslib
│   ├── imm32_ghidra.fkslib
│   ├── inetcpl_ghidra.fkslib
│   ├── InputService_arm64_ghidra.fkslib
│   ├── inputservice_ghidra.fkslib
│   ├── InstallService_arm64_ghidra.fkslib
│   ├── intelsst_ghidra.fkslib
│   ├── iphlpapi_arm64_ghidra.fkslib
│   ├── iphlpapi_ghidra.fkslib
│   ├── isl23_ghidra.fkslib
│   ├── jscript_arm64_ghidra.fkslib
│   ├── jscript_ghidra.fkslib
│   ├── jscript9_arm64_ghidra.fkslib
│   ├── jscript9_ghidra.fkslib
│   ├── jscript9legacy_arm64_ghidra.fkslib
│   ├── kernel32_arm64_ghidra.fkslib
│   ├── kernel32_ghidra.fkslib
│   ├── kernelbase_arm64_ghidra.fkslib
│   ├── kernelbase_ghidra.fkslib
│   ├── keycredmgr_ghidra.fkslib
│   ├── ksuser_ghidra.fkslib
│   ├── ktmw32_ghidra.fkslib
│   ├── libbz2_ghidra.fkslib
│   ├── libcapstone_ghidra.fkslib
│   ├── libcrypto3_ghidra.fkslib
│   ├── libcurl4_ghidra.fkslib
│   ├── libexpat_ghidra.fkslib
│   ├── libffi_ghidra.fkslib
│   ├── libfreetype_ghidra.fkslib
│   ├── libgcc_s_mingw_ghidra.fkslib
│   ├── libgio_ghidra.fkslib
│   ├── libglib_ghidra.fkslib
│   ├── libgobject_ghidra.fkslib
│   ├── libharfbuzz_ghidra.fkslib
│   ├── libjpeg8_ghidra.fkslib
│   ├── liblzma5_ghidra.fkslib
│   ├── libnghttp2_ghidra.fkslib
│   ├── libpcre2_16_ghidra.fkslib
│   ├── libpcre2_32_ghidra.fkslib
│   ├── libpcre2_8_ghidra.fkslib
│   ├── libpcre2_posix_ghidra.fkslib
│   ├── libpng16_ghidra.fkslib
│   ├── libssl3_ghidra.fkslib
│   ├── libssl3_msys2_ghidra.fkslib
│   ├── libstdcpp_mingw_ghidra.fkslib
│   ├── libwinpthread_mingw_ghidra.fkslib
│   ├── llvm21.fkslib
│   ├── loadperf_ghidra.fkslib
│   ├── lsasrv_ghidra.fkslib
│   ├── magnification_ghidra.fkslib
│   ├── mapi32_ghidra.fkslib
│   ├── MapRouter_arm64_ghidra.fkslib
│   ├── MdmDiagnostics_arm64_ghidra.fkslib
│   ├── mfc100_ghidra.fkslib
│   ├── mfc100u_ghidra.fkslib
│   ├── mfc110_ghidra.fkslib
│   ├── mfc110u_ghidra.fkslib
│   ├── mfc120_ghidra.fkslib
│   ├── mfc120u_ghidra.fkslib
│   ├── mfc140_arm64_ghidra.fkslib
│   ├── mfc140_ghidra.fkslib
│   ├── mfc140u_arm64_ghidra.fkslib
│   ├── mfc140u_ghidra.fkslib
│   ├── mfcm140_arm64_ghidra.fkslib
│   ├── mfcm140u_arm64_ghidra.fkslib
│   ├── mfcore_arm64_ghidra.fkslib
│   ├── mfcore_ghidra.fkslib
│   ├── mfmediaengine_arm64_ghidra.fkslib
│   ├── mfmp4srcsnk_arm64_ghidra.fkslib
│   ├── mfplat_arm64_ghidra.fkslib
│   ├── mfplat_ghidra.fkslib
│   ├── mispace_arm64_ghidra.fkslib
│   ├── mlang_ghidra.fkslib
│   ├── mpr_ghidra.fkslib
│   ├── mprapi_ghidra.fkslib
│   ├── msacm32_ghidra.fkslib
│   ├── msctf_ghidra.fkslib
│   ├── msdart_ghidra.fkslib
│   ├── msdelta_ghidra.fkslib
│   ├── msdmo_ghidra.fkslib
│   ├── msfeeds_arm64_ghidra.fkslib
│   ├── msfeedsbs_arm64_ghidra.fkslib
│   ├── msftedit_arm64_ghidra.fkslib
│   ├── msftedit_ghidra.fkslib
│   ├── mshtml_arm64_ghidra.fkslib
│   ├── mshtml_ghidra.fkslib
│   ├── msi_arm64_ghidra.fkslib
│   ├── msi_ghidra.fkslib
│   ├── msimg32_ghidra.fkslib
│   ├── msports_ghidra.fkslib
│   ├── msrating_arm64_ghidra.fkslib
│   ├── msrle32_ghidra.fkslib
│   ├── mssrch_arm64_ghidra.fkslib
│   ├── mstscax_arm64_ghidra.fkslib
│   ├── mstscax_ghidra.fkslib
│   ├── msvcp_win_ghidra.fkslib
│   ├── msvcp100_ghidra.fkslib
│   ├── msvcp110_ghidra.fkslib
│   ├── msvcp110_win_ghidra.fkslib
│   ├── msvcp120_ghidra.fkslib
│   ├── msvcp140_1_arm64_ghidra.fkslib
│   ├── msvcp140_1_ghidra.fkslib
│   ├── msvcp140_2_arm64_ghidra.fkslib
│   ├── msvcp140_2_ghidra.fkslib
│   ├── msvcp140_arm64_ghidra.fkslib
│   ├── msvcp140_atomic_wait_arm64_ghidra.fkslib
│   ├── msvcp140_atomic_wait_ghidra.fkslib
│   ├── msvcp140_codecvt_ids_arm64_ghidra.fkslib
│   ├── msvcp140_codecvt_ids_ghidra.fkslib
│   ├── msvcp140_ghidra.fkslib
│   ├── msvcp60_ghidra.fkslib
│   ├── msvcrt_arm64_ghidra.fkslib
│   ├── msvcrt_ghidra.fkslib
│   ├── msvfw32_ghidra.fkslib
│   ├── msvidc32_ghidra.fkslib
│   ├── msxml3_ghidra.fkslib
│   ├── msxml6_ghidra.fkslib
│   ├── ncrypt_arm64_ghidra.fkslib
│   ├── ncrypt_ghidra.fkslib
│   ├── netapi32_ghidra.fkslib
│   ├── netutils_ghidra.fkslib
│   ├── newdev_ghidra.fkslib
│   ├── ninput_ghidra.fkslib
│   ├── nlaapi_ghidra.fkslib
│   ├── NlsData0009_arm64_ghidra.fkslib
│   ├── nshwfp_ghidra.fkslib
│   ├── ntdll_arm64_ghidra.fkslib
│   ├── ntdll_ghidra.fkslib
│   ├── ntmarta_ghidra.fkslib
│   ├── ntoskrnl_ghidra.fkslib
│   ├── ntshrui_ghidra.fkslib
│   ├── odbc32_ghidra.fkslib
│   ├── ole32_arm64_ghidra.fkslib
│   ├── ole32_ghidra.fkslib
│   ├── oleacc_ghidra.fkslib
│   ├── oleaut32_arm64_ghidra.fkslib
│   ├── oleaut32_ghidra.fkslib
│   ├── oledlg_arm64_ghidra.fkslib
│   ├── oledlg_ghidra.fkslib
│   ├── OneCoreUAPCommonProxyStub_arm64_ghidra.fkslib
│   ├── onnxruntime_arm64_arm64_ghidra.fkslib
│   ├── onnxruntime_x64_arm64_ghidra.fkslib
│   ├── opengl32_arm64_ghidra.fkslib
│   ├── opengl32_ghidra.fkslib
│   ├── p11_kit_ghidra.fkslib
│   ├── pdh_ghidra.fkslib
│   ├── pnrpauto_ghidra.fkslib
│   ├── pnrpnsp_ghidra.fkslib
│   ├── policymanager_ghidra.fkslib
│   ├── portabledeviceapi_ghidra.fkslib
│   ├── powrprof_arm64_ghidra.fkslib
│   ├── powrprof_ghidra.fkslib
│   ├── printui_ghidra.fkslib
│   ├── prntvpt_ghidra.fkslib
│   ├── profapi_arm64_ghidra.fkslib
│   ├── profapi_ghidra.fkslib
│   ├── propsys_arm64_ghidra.fkslib
│   ├── propsys_ghidra.fkslib
│   ├── psapi_arm64_ghidra.fkslib
│   ├── psapi_ghidra.fkslib
│   ├── python311_ghidra.fkslib
│   ├── python312_ghidra.fkslib
│   ├── qt6concurrent_ghidra.fkslib
│   ├── qt6core_ghidra.fkslib
│   ├── qt6dbus_ghidra.fkslib
│   ├── qt6designer_ghidra.fkslib
│   ├── qt6designercomponents_ghidra.fkslib
│   ├── qt6gui_ghidra.fkslib
│   ├── qt6help_ghidra.fkslib
│   ├── qt6network_ghidra.fkslib
│   ├── qt6opengl_ghidra.fkslib
│   ├── qt6openglwidgets_ghidra.fkslib
│   ├── qt6print_ghidra.fkslib
│   ├── qt6sql_ghidra.fkslib
│   ├── qt6test_ghidra.fkslib
│   ├── qt6uitools_ghidra.fkslib
│   ├── qt6widgets_ghidra.fkslib
│   ├── qt6xml_ghidra.fkslib
│   ├── quartz_ghidra.fkslib
│   ├── rasapi32_ghidra.fkslib
│   ├── rasdlg_ghidra.fkslib
│   ├── rasman_ghidra.fkslib
│   ├── resourcepolicyclient_ghidra.fkslib
│   ├── resutils_arm64_ghidra.fkslib
│   ├── resutils_ghidra.fkslib
│   ├── riched20_ghidra.fkslib
│   ├── rpcrt4_arm64_ghidra.fkslib
│   ├── rpcrt4_ghidra.fkslib
│   ├── rsaenh_ghidra.fkslib
│   ├── rtmpltfm_ghidra.fkslib
│   ├── rust_runtime.fkslib
│   ├── rust_std.fkslib
│   ├── samcli_ghidra.fkslib
│   ├── samsrv_ghidra.fkslib
│   ├── sas_ghidra.fkslib
│   ├── schannel_ghidra.fkslib
│   ├── scrrun_ghidra.fkslib
│   ├── sechost_arm64_ghidra.fkslib
│   ├── sechost_ghidra.fkslib
│   ├── secur32_ghidra.fkslib
│   ├── sensapi_ghidra.fkslib
│   ├── SettingsHandlers_nt_arm64_ghidra.fkslib
│   ├── setupapi_arm64_ghidra.fkslib
│   ├── setupapi_ghidra.fkslib
│   ├── shell32_arm64_ghidra.fkslib
│   ├── shell32_ghidra.fkslib
│   ├── shlwapi_arm64_ghidra.fkslib
│   ├── shlwapi_ghidra.fkslib
│   ├── sppc_ghidra.fkslib
│   ├── sppwinob_ghidra.fkslib
│   ├── sqlite3_msys2_ghidra.fkslib
│   ├── SRH_arm64_ghidra.fkslib
│   ├── srvsvc_ghidra.fkslib
│   ├── sspicli_ghidra.fkslib
│   ├── StartTileData_arm64_ghidra.fkslib
│   ├── stdcpp6_msys2_ghidra.fkslib
│   ├── sti_ghidra.fkslib
│   ├── structuredquery_ghidra.fkslib
│   ├── SystemSettingsThresholdAdminFlowUI_arm64_ghidra.fkslib
│   ├── tapi32_ghidra.fkslib
│   ├── tbs_ghidra.fkslib
│   ├── tcl86_ghidra.fkslib
│   ├── tcpipcfg_ghidra.fkslib
│   ├── thumbcache_arm64_ghidra.fkslib
│   ├── thumbcache_ghidra.fkslib
│   ├── tk86_ghidra.fkslib
│   ├── tquery_arm64_ghidra.fkslib
│   ├── twinapi_appcore_ghidra.fkslib
│   ├── twinui_arm64_ghidra.fkslib
│   ├── twinui_ghidra.fkslib
│   ├── twinui_pcshell_arm64_ghidra.fkslib
│   ├── twinui_pcshell_ghidra.fkslib
│   ├── txflog_ghidra.fkslib
│   ├── ucrtbase_arm64_ghidra.fkslib
│   ├── ucrtbase_ghidra.fkslib
│   ├── UdiApiClient_arm64_ghidra.fkslib
│   ├── UIAutomationCore_arm64_ghidra.fkslib
│   ├── uiautomationcore_ghidra.fkslib
│   ├── UIRibbon_arm64_ghidra.fkslib
│   ├── unistring5_ghidra.fkslib
│   ├── urlmon_arm64_ghidra.fkslib
│   ├── urlmon_ghidra.fkslib
│   ├── user32_arm64_ghidra.fkslib
│   ├── user32_ghidra.fkslib
│   ├── userenv_ghidra.fkslib
│   ├── uxtheme_arm64_ghidra.fkslib
│   ├── uxtheme_ghidra.fkslib
│   ├── vbscript_arm64_ghidra.fkslib
│   ├── vbscript_ghidra.fkslib
│   ├── vcamp140_arm64_ghidra.fkslib
│   ├── vccorlib140_arm64_ghidra.fkslib
│   ├── vcomp140_arm64_ghidra.fkslib
│   ├── vcomp140_ghidra.fkslib
│   ├── vcruntime140_1_ghidra.fkslib
│   ├── vcruntime140_arm64_ghidra.fkslib
│   ├── vcruntime140_ghidra.fkslib
│   ├── vcruntime140_threads_arm64_ghidra.fkslib
│   ├── vcruntime140_threads_ghidra.fkslib
│   ├── version_arm64_ghidra.fkslib
│   ├── version_ghidra.fkslib
│   ├── vssapi_ghidra.fkslib
│   ├── wcnapi_ghidra.fkslib
│   ├── wdigest_ghidra.fkslib
│   ├── wdmaud_ghidra.fkslib
│   ├── webservices_ghidra.fkslib
│   ├── wecapi_arm64_ghidra.fkslib
│   ├── wecapi_ghidra.fkslib
│   ├── wer_arm64_ghidra.fkslib
│   ├── wer_ghidra.fkslib
│   ├── wercplsupport_arm64_ghidra.fkslib
│   ├── wiadefui_ghidra.fkslib
│   ├── wiaservc_ghidra.fkslib
│   ├── wimgapi_ghidra.fkslib
│   ├── win32u_arm64_ghidra.fkslib
│   ├── win32u_ghidra.fkslib
│   ├── windows_ai_ml_ghidra.fkslib
│   ├── windows_applicationmodel_store_arm64_ghidra.fkslib
│   ├── windows_cloudstore_arm64_ghidra.fkslib
│   ├── windows_codecs_raw_ghidra.fkslib
│   ├── windows_data_pdf_arm64_ghidra.fkslib
│   ├── windows_media_arm64_ghidra.fkslib
│   ├── windows_media_ghidra.fkslib
│   ├── windows_media_protection_playready_arm64_ghidra.fkslib
│   ├── windows_state_repo_ghidra.fkslib
│   ├── windows_staterepository_arm64_ghidra.fkslib
│   ├── windows_storage_arm64_ghidra.fkslib
│   ├── windows_storage_ghidra.fkslib
│   ├── windows_ui_cred_arm64_ghidra.fkslib
│   ├── windows_ui_logon_arm64_ghidra.fkslib
│   ├── windows_ui_xaml_arm64_ghidra.fkslib
│   ├── windows_ui_xaml_controls_arm64_ghidra.fkslib
│   ├── windows_uixaml_ghidra.fkslib
│   ├── windowscodecs_arm64_ghidra.fkslib
│   ├── WindowsCodecs_ghidra.fkslib
│   ├── windowsudk_shellcommon_arm64_ghidra.fkslib
│   ├── winhttp_arm64_ghidra.fkslib
│   ├── winhttp_ghidra.fkslib
│   ├── wininet_arm64_ghidra.fkslib
│   ├── wininet_ghidra.fkslib
│   ├── winmm_arm64_ghidra.fkslib
│   ├── winmm_ghidra.fkslib
│   ├── winmmbase_ghidra.fkslib
│   ├── winscard_ghidra.fkslib
│   ├── winspool_ghidra.fkslib
│   ├── winsqlite3_ghidra.fkslib
│   ├── winsta_arm64_ghidra.fkslib
│   ├── winsta_ghidra.fkslib
│   ├── wintrust_arm64_ghidra.fkslib
│   ├── wintrust_ghidra.fkslib
│   ├── winusb_ghidra.fkslib
│   ├── wkssvc_ghidra.fkslib
│   ├── wlanapi_ghidra.fkslib
│   ├── wmadmod_arm64_ghidra.fkslib
│   ├── wmasf_arm64_ghidra.fkslib
│   ├── wmnetmgr_arm64_ghidra.fkslib
│   ├── wmp_arm64_ghidra.fkslib
│   ├── wmp_ghidra.fkslib
│   ├── wmvcore_arm64_ghidra.fkslib
│   ├── ws2_32_arm64_ghidra.fkslib
│   ├── ws2_32_ghidra.fkslib
│   ├── WsmSvc_arm64_ghidra.fkslib
│   ├── wtsapi32_arm64_ghidra.fkslib
│   ├── wtsapi32_ghidra.fkslib
│   ├── X3DAudio1_7_ghidra.fkslib
│   ├── XAudio2_9_ghidra.fkslib
│   ├── XInput1_3_ghidra.fkslib
│   ├── XInput1_4_ghidra.fkslib
│   ├── xmllite_ghidra.fkslib
│   ├── xolehlp_ghidra.fkslib
│   └── zlib1_ghidra.fkslib
├── include
│   └── ghidra
│       └── PropertyMapManagerImpl.h
├── schemas
│   ├── changeset.fbs
│   ├── commit.fbs
│   ├── fks.fbs
│   ├── program.fbs
│   └── project.fbs
├── sleigh
│   ├── 6502
│   │   ├── 6502.cspec
│   │   ├── 6502.ldefs
│   │   ├── 6502.pspec
│   │   ├── 6502.sla
│   │   ├── 6502.slaspec
│   │   ├── 65c02.sla
│   │   └── 65c02.slaspec
│   ├── 68000
│   │   ├── 68000_register.cspec
│   │   ├── 68000.cspec
│   │   ├── 68000.ldefs
│   │   ├── 68000.pspec
│   │   ├── 68000.sinc
│   │   ├── 68020.sla
│   │   ├── 68020.slaspec
│   │   ├── 68030.sla
│   │   ├── 68030.slaspec
│   │   ├── 68040.sla
│   │   ├── 68040.slaspec
│   │   ├── coldfire.sla
│   │   ├── coldfire.slaspec
│   │   ├── CPU32.sla
│   │   └── CPU32.slaspec
│   ├── 8048
│   │   ├── 8048.cspec
│   │   ├── 8048.ldefs
│   │   ├── 8048.pspec
│   │   ├── 8048.sla
│   │   └── 8048.slaspec
│   ├── 8051
│   │   ├── 80251.cspec
│   │   ├── 80251.pspec
│   │   ├── 80251.sinc
│   │   ├── 80251.sla
│   │   ├── 80251.slaspec
│   │   ├── 80390.cspec
│   │   ├── 80390.sla
│   │   ├── 80390.slaspec
│   │   ├── 8051_archimedes.cspec
│   │   ├── 8051_main.sinc
│   │   ├── 8051.cspec
│   │   ├── 8051.ldefs
│   │   ├── 8051.pspec
│   │   ├── 8051.sla
│   │   ├── 8051.slaspec
│   │   ├── cip-51.sla
│   │   ├── cip-51.slaspec
│   │   ├── keil-cx51.cspec
│   │   ├── mx51.cspec
│   │   ├── mx51.pspec
│   │   ├── mx51.sinc
│   │   ├── mx51.sla
│   │   └── mx51.slaspec
│   ├── 8085
│   │   ├── 8085.ldefs
│   │   ├── 8085.sla
│   │   └── 8085.slaspec
│   ├── AARCH64
│   │   ├── AARCH64_AMXext.sinc
│   │   ├── AARCH64_apple.cspec
│   │   ├── AARCH64_AppleSilicon.sla
│   │   ├── AARCH64_AppleSilicon.slaspec
│   │   ├── AARCH64_base_PACoptions.sinc
│   │   ├── AARCH64_golang.cspec
│   │   ├── AARCH64_ilp32.cspec
│   │   ├── AARCH64_swift.cspec
│   │   ├── AARCH64_win.cspec
│   │   ├── AARCH64.cspec
│   │   ├── AARCH64.ldefs
│   │   ├── AARCH64.pspec
│   │   ├── AARCH64.sla
│   │   ├── AARCH64.slaspec
│   │   ├── AARCH64base.sinc
│   │   ├── AARCH64BE.sla
│   │   ├── AARCH64BE.slaspec
│   │   ├── AARCH64instructions.sinc
│   │   ├── AARCH64ldst.sinc
│   │   ├── AARCH64neon.sinc
│   │   ├── AARCH64sve.sinc
│   │   └── AppleSilicon.ldefs
│   ├── ARM
│   │   ├── ARM_apcs.cspec
│   │   ├── ARM_CDE.sinc
│   │   ├── ARM_v45.cspec
│   │   ├── ARM_v45.pspec
│   │   ├── ARM_win.cspec
│   │   ├── ARM.cspec
│   │   ├── ARM.ldefs
│   │   ├── ARM.sinc
│   │   ├── ARM4_be.sla
│   │   ├── ARM4_be.slaspec
│   │   ├── ARM4_le.sla
│   │   ├── ARM4_le.slaspec
│   │   ├── ARM4t_be.sla
│   │   ├── ARM4t_be.slaspec
│   │   ├── ARM4t_le.sla
│   │   ├── ARM4t_le.slaspec
│   │   ├── ARM5_be.sla
│   │   ├── ARM5_be.slaspec
│   │   ├── ARM5_le.sla
│   │   ├── ARM5_le.slaspec
│   │   ├── ARM5t_be.sla
│   │   ├── ARM5t_be.slaspec
│   │   ├── ARM5t_le.sla
│   │   ├── ARM5t_le.slaspec
│   │   ├── ARM6_be.sla
│   │   ├── ARM6_be.slaspec
│   │   ├── ARM6_le.sla
│   │   ├── ARM6_le.slaspec
│   │   ├── ARM7_be.sla
│   │   ├── ARM7_be.slaspec
│   │   ├── ARM7_le.sla
│   │   ├── ARM7_le.slaspec
│   │   ├── ARM8_be.sla
│   │   ├── ARM8_be.slaspec
│   │   ├── ARM8_le.sla
│   │   ├── ARM8_le.slaspec
│   │   ├── ARM8m_be.sla
│   │   ├── ARM8m_be.slaspec
│   │   ├── ARM8m_le.sla
│   │   ├── ARM8m_le.slaspec
│   │   ├── ARMCortex.pspec
│   │   ├── ARMinstructions.sinc
│   │   ├── ARMneon.sinc
│   │   ├── ARMt_v45.pspec
│   │   ├── ARMt_v6.pspec
│   │   ├── ARMt.pspec
│   │   ├── ARMTHUMBinstructions.sinc
│   │   ├── ARMtTHUMB.pspec
│   │   └── ARMv8.sinc
│   ├── Atmel
│   │   ├── avr32a_arithmetic_operations.sinc
│   │   ├── avr32a_autogen.sinc
│   │   ├── avr32a_bit_operations.sinc
│   │   ├── avr32a_coprocessor_interface.sinc
│   │   ├── avr32a_data_transfer.sinc
│   │   ├── avr32a_dsp_operations.sinc
│   │   ├── avr32a_dsp_operations2.sinc
│   │   ├── avr32a_instruction_flow.sinc
│   │   ├── avr32a_logic_operations.sinc
│   │   ├── avr32a_multiplication_operations.sinc
│   │   ├── avr32a_shift_operations.sinc
│   │   ├── avr32a_simd_operations.sinc
│   │   ├── avr32a_system_control.sinc
│   │   ├── avr32a.ldefs
│   │   ├── avr32a.sla
│   │   ├── avr32a.slaspec
│   │   ├── avr8.ldefs
│   │   ├── avr8.sinc
│   │   ├── avr8.sla
│   │   ├── avr8.slaspec
│   │   ├── avr8e.sla
│   │   ├── avr8e.slaspec
│   │   ├── avr8eind.sla
│   │   ├── avr8eind.slaspec
│   │   ├── avr8xmega.sla
│   │   └── avr8xmega.slaspec
│   ├── BPF
│   │   ├── BPF_le.sla
│   │   ├── BPF_le.slaspec
│   │   ├── BPF.cspec
│   │   ├── BPF.ldefs
│   │   ├── BPF.pspec
│   │   └── BPF.sinc
│   ├── CP1600
│   │   ├── CP1600.ldefs
│   │   ├── CP1600.sla
│   │   └── CP1600.slaspec
│   ├── CR16
│   │   ├── CR16.ldefs
│   │   ├── CR16B.sinc
│   │   ├── CR16B.sla
│   │   ├── CR16B.slaspec
│   │   ├── CR16C.sinc
│   │   ├── CR16C.sla
│   │   └── CR16C.slaspec
│   ├── Dalvik
│   │   ├── Dalvik_Base.cspec
│   │   ├── Dalvik_Base.pspec
│   │   ├── Dalvik_Base.sinc
│   │   ├── Dalvik_Base.sla
│   │   ├── Dalvik_Base.slaspec
│   │   ├── Dalvik_DEX_Android10.sla
│   │   ├── Dalvik_DEX_Android10.slaspec
│   │   ├── Dalvik_DEX_Android11.sla
│   │   ├── Dalvik_DEX_Android11.slaspec
│   │   ├── Dalvik_DEX_Android12.sla
│   │   ├── Dalvik_DEX_Android12.slaspec
│   │   ├── Dalvik_DEX_KitKat.sla
│   │   ├── Dalvik_DEX_KitKat.slaspec
│   │   ├── Dalvik_DEX_Lollipop.sla
│   │   ├── Dalvik_DEX_Lollipop.slaspec
│   │   ├── Dalvik_DEX_Marshmallow.sla
│   │   ├── Dalvik_DEX_Marshmallow.slaspec
│   │   ├── Dalvik_DEX_Nougat.sla
│   │   ├── Dalvik_DEX_Nougat.slaspec
│   │   ├── Dalvik_DEX_Oreo.sla
│   │   ├── Dalvik_DEX_Oreo.slaspec
│   │   ├── Dalvik_DEX_Pie.sla
│   │   ├── Dalvik_DEX_Pie.slaspec
│   │   ├── Dalvik_ODEX_KitKat.sla
│   │   ├── Dalvik_ODEX_KitKat.slaspec
│   │   ├── Dalvik_OpCode_3E_43_unused.sinc
│   │   ├── Dalvik_OpCode_73_return_void_barrier.sinc
│   │   ├── Dalvik_OpCode_73_return_void_no_barrier.sinc
│   │   ├── Dalvik_OpCode_73_unused.sinc
│   │   ├── Dalvik_OpCode_79_unused.sinc
│   │   ├── Dalvik_OpCode_7A_unused.sinc
│   │   ├── Dalvik_OpCode_E3_EA_dex.sinc
│   │   ├── Dalvik_OpCode_E3_EA_unused.sinc
│   │   ├── Dalvik_OpCode_EB_F2_iput_iget.sinc
│   │   ├── Dalvik_OpCode_EB_F2_unused.sinc
│   │   ├── Dalvik_OpCode_F3_unused.sinc
│   │   ├── Dalvik_OpCode_F4_unused.sinc
│   │   ├── Dalvik_OpCode_F5_unused.sinc
│   │   ├── Dalvik_OpCode_F6_unused.sinc
│   │   ├── Dalvik_OpCode_F7_unused.sinc
│   │   ├── Dalvik_OpCode_F8_unused.sinc
│   │   ├── Dalvik_OpCode_F9_unused.sinc
│   │   ├── Dalvik_OpCode_FA_FD_dex.sinc
│   │   ├── Dalvik_OpCode_FA_unused.sinc
│   │   ├── Dalvik_OpCode_FB_unused.sinc
│   │   ├── Dalvik_OpCode_FC_unused.sinc
│   │   ├── Dalvik_OpCode_FD_unused.sinc
│   │   ├── Dalvik_OpCode_FE_FF_dex.sinc
│   │   ├── Dalvik_OpCode_FE_unused.sinc
│   │   ├── Dalvik_OpCode_FF_unused.sinc
│   │   └── Dalvik.ldefs
│   ├── DATA
│   │   ├── data-be-64.sla
│   │   ├── data-be-64.slaspec
│   │   ├── data-le-64.sla
│   │   ├── data-le-64.slaspec
│   │   ├── data.ldefs
│   │   └── data.sinc
│   ├── eBPF
│   │   ├── eBPF_be.sla
│   │   ├── eBPF_be.slaspec
│   │   ├── eBPF_le.sla
│   │   ├── eBPF_le.slaspec
│   │   ├── eBPF.cspec
│   │   ├── eBPF.ldefs
│   │   ├── eBPF.pspec
│   │   └── eBPF.sinc
│   ├── HCS08
│   │   ├── HC05.ldefs
│   │   ├── HC05.sla
│   │   ├── HC05.slaspec
│   │   ├── HC08.ldefs
│   │   ├── HC08.sla
│   │   ├── HC08.slaspec
│   │   ├── HCS_HC.sinc
│   │   ├── HCS08.ldefs
│   │   ├── HCS08.sla
│   │   └── HCS08.slaspec
│   ├── HCS12
│   │   ├── HC12.sla
│   │   ├── HC12.slaspec
│   │   ├── HCS_HC12.sinc
│   │   ├── HCS12.ldefs
│   │   ├── HCS12.sla
│   │   ├── HCS12.slaspec
│   │   ├── HCS12X.sla
│   │   ├── HCS12X.slaspec
│   │   └── XGATE.sinc
│   ├── Hexagon
│   │   ├── hexagon_float.sinc
│   │   ├── hexagon_hvx.sinc
│   │   ├── hexagon_left.sinc
│   │   ├── hexagon_right.sinc
│   │   ├── hexagon.cspec
│   │   ├── hexagon.ldefs
│   │   ├── hexagon.pspec
│   │   ├── hexagon.sinc
│   │   ├── hexagon.sla
│   │   └── hexagon.slaspec
│   ├── JVM
│   │   ├── JVM.cspec
│   │   ├── JVM.ldefs
│   │   ├── JVM.pspec
│   │   ├── JVM.sla
│   │   └── JVM.slaspec
│   ├── Loongarch
│   │   ├── ilp32d.cspec
│   │   ├── ilp32f.cspec
│   │   ├── lasx.sinc
│   │   ├── lbt.sinc
│   │   ├── loongarch_double.sinc
│   │   ├── loongarch_float.sinc
│   │   ├── loongarch_main.sinc
│   │   ├── loongarch.ldefs
│   │   ├── loongarch32_f32.sla
│   │   ├── loongarch32_f32.slaspec
│   │   ├── loongarch32_f64.sla
│   │   ├── loongarch32_f64.slaspec
│   │   ├── loongarch32_instructions.sinc
│   │   ├── loongarch32.pspec
│   │   ├── loongarch64_f32.sla
│   │   ├── loongarch64_f32.slaspec
│   │   ├── loongarch64_f64.sla
│   │   ├── loongarch64_f64.slaspec
│   │   ├── loongarch64_instructions.sinc
│   │   ├── loongarch64.pspec
│   │   ├── lp64d.cspec
│   │   ├── lp64f.cspec
│   │   ├── lsx.sinc
│   │   └── lvz.sinc
│   ├── M16C
│   │   ├── M16C_60.ldefs
│   │   ├── M16C_60.sla
│   │   ├── M16C_60.slaspec
│   │   ├── M16C_80.ldefs
│   │   ├── M16C_80.sla
│   │   └── M16C_80.slaspec
│   ├── M8C
│   │   ├── m8c.ldefs
│   │   ├── m8c.sla
│   │   └── m8c.slaspec
│   ├── MC6800
│   │   ├── 6800.ldefs
│   │   ├── 6805.ldefs
│   │   ├── 6805.sla
│   │   ├── 6805.slaspec
│   │   ├── 6809.sla
│   │   ├── 6809.slaspec
│   │   ├── 6x09_exg_tfr.sinc
│   │   ├── 6x09_pull.sinc
│   │   ├── 6x09_push.sinc
│   │   ├── 6x09.sinc
│   │   ├── H6309.sla
│   │   └── H6309.slaspec
│   ├── MCS96
│   │   ├── MCS96.ldefs
│   │   ├── MCS96.sinc
│   │   ├── MCS96.sla
│   │   └── MCS96.slaspec
│   ├── MIPS
│   │   ├── mips_dsp.sinc
│   │   ├── mips_mt.sinc
│   │   ├── mips.ldefs
│   │   ├── mips.sinc
│   │   ├── mips16.sinc
│   │   ├── mips32_16e.pspec
│   │   ├── mips32_eabi.cspec
│   │   ├── mips32_fp64.cspec
│   │   ├── mips32.pspec
│   │   ├── mips32be.cspec
│   │   ├── mips32be.sla
│   │   ├── mips32be.slaspec
│   │   ├── mips32Instructions.sinc
│   │   ├── mips32le.cspec
│   │   ├── mips32le.sla
│   │   ├── mips32le.slaspec
│   │   ├── mips32micro.pspec
│   │   ├── mips32R6.pspec
│   │   ├── mips32R6be.sla
│   │   ├── mips32R6be.slaspec
│   │   ├── mips32R6le.sla
│   │   ├── mips32R6le.slaspec
│   │   ├── mips64_16e.pspec
│   │   ├── mips64_32_n32.cspec
│   │   ├── mips64_32_o32.cspec
│   │   ├── mips64_32_o64.cspec
│   │   ├── mips64.pspec
│   │   ├── mips64be.cspec
│   │   ├── mips64be.sla
│   │   ├── mips64be.slaspec
│   │   ├── mips64Instructions.sinc
│   │   ├── mips64le.cspec
│   │   ├── mips64le.sla
│   │   ├── mips64le.slaspec
│   │   ├── mips64micro.pspec
│   │   ├── mips64R6.pspec
│   │   ├── mipsfloat.sinc
│   │   └── mipsmicro.sinc
│   ├── NDS32
│   │   ├── lsmw.sinc
│   │   ├── nds32.cspec
│   │   ├── nds32.ldefs
│   │   ├── nds32.pspec
│   │   ├── nds32.sinc
│   │   ├── nds32be.sla
│   │   ├── nds32be.slaspec
│   │   ├── nds32le.sla
│   │   └── nds32le.slaspec
│   ├── PA-RISC
│   │   ├── pa-risc.ldefs
│   │   ├── pa-risc.sinc
│   │   ├── pa-risc32.cspec
│   │   ├── pa-risc32.pspec
│   │   ├── pa-risc32be.sla
│   │   ├── pa-risc32be.slaspec
│   │   └── pa-riscInstructions.sinc
│   ├── PIC
│   │   ├── dsPIC30F.sla
│   │   ├── dsPIC30F.slaspec
│   │   ├── dsPIC33C.sla
│   │   ├── dsPIC33C.slaspec
│   │   ├── dsPIC33E.sla
│   │   ├── dsPIC33E.slaspec
│   │   ├── dsPIC33F.sla
│   │   ├── dsPIC33F.slaspec
│   │   ├── pic12_instructions.sinc
│   │   ├── pic12.sinc
│   │   ├── pic12c5xx.cspec
│   │   ├── pic12c5xx.ldefs
│   │   ├── pic12c5xx.pspec
│   │   ├── pic12c5xx.sla
│   │   ├── pic12c5xx.slaspec
│   │   ├── pic16_instructions.sinc
│   │   ├── pic16.cspec
│   │   ├── pic16.ldefs
│   │   ├── pic16.pspec
│   │   ├── pic16.sinc
│   │   ├── pic16.sla
│   │   ├── pic16.slaspec
│   │   ├── pic16c5x.cspec
│   │   ├── pic16c5x.ldefs
│   │   ├── pic16c5x.pspec
│   │   ├── pic16c5x.sla
│   │   ├── pic16c5x.slaspec
│   │   ├── pic16f.cspec
│   │   ├── pic16f.pspec
│   │   ├── pic16f.sla
│   │   ├── pic16f.slaspec
│   │   ├── pic17c7xx_instructions.sinc
│   │   ├── pic17c7xx.cspec
│   │   ├── pic17c7xx.ldefs
│   │   ├── pic17c7xx.pspec
│   │   ├── pic17c7xx.sinc
│   │   ├── pic17c7xx.sla
│   │   ├── pic17c7xx.slaspec
│   │   ├── pic18_instructions.sinc
│   │   ├── pic18.cspec
│   │   ├── pic18.ldefs
│   │   ├── pic18.pspec
│   │   ├── pic18.sinc
│   │   ├── pic18.sla
│   │   ├── pic18.slaspec
│   │   ├── PIC24.cspec
│   │   ├── PIC24.ldefs
│   │   ├── PIC24.pspec
│   │   ├── PIC24.sinc
│   │   ├── PIC24E.sla
│   │   ├── PIC24E.slaspec
│   │   ├── PIC24F.sla
│   │   ├── PIC24F.slaspec
│   │   ├── PIC24H.sla
│   │   └── PIC24H.slaspec
│   ├── PowerPC
│   │   ├── 4xx.sinc
│   │   ├── altivec.sinc
│   │   ├── evx.sinc
│   │   ├── FPRC.sinc
│   │   ├── g2.sinc
│   │   ├── lmwInstructions.sinc
│   │   ├── lswInstructions.sinc
│   │   ├── mulhwInstructions.sinc
│   │   ├── ppc_32_4xx_be.sla
│   │   ├── ppc_32_4xx_be.slaspec
│   │   ├── ppc_32_4xx_le.sla
│   │   ├── ppc_32_4xx_le.slaspec
│   │   ├── ppc_32_be_Mac.cspec
│   │   ├── ppc_32_be.sla
│   │   ├── ppc_32_be.slaspec
│   │   ├── ppc_32_e500_be.cspec
│   │   ├── ppc_32_e500_be.sla
│   │   ├── ppc_32_e500_be.slaspec
│   │   ├── ppc_32_e500_le.cspec
│   │   ├── ppc_32_e500_le.sla
│   │   ├── ppc_32_e500_le.slaspec
│   │   ├── ppc_32_e500mc_be.cspec
│   │   ├── ppc_32_e500mc_be.sla
│   │   ├── ppc_32_e500mc_be.slaspec
│   │   ├── ppc_32_e500mc_le.cspec
│   │   ├── ppc_32_e500mc_le.sla
│   │   ├── ppc_32_e500mc_le.slaspec
│   │   ├── ppc_32_le.sla
│   │   ├── ppc_32_le.slaspec
│   │   ├── ppc_32_mpc8270.pspec
│   │   ├── ppc_32_quicciii_be.sla
│   │   ├── ppc_32_quicciii_be.slaspec
│   │   ├── ppc_32_quicciii_le.sla
│   │   ├── ppc_32_quicciii_le.slaspec
│   │   ├── ppc_32.cspec
│   │   ├── ppc_32.pspec
│   │   ├── ppc_64_32.cspec
│   │   ├── ppc_64_be_Mac.cspec
│   │   ├── ppc_64_be.cspec
│   │   ├── ppc_64_be.sla
│   │   ├── ppc_64_be.slaspec
│   │   ├── ppc_64_isa_altivec_be.sla
│   │   ├── ppc_64_isa_altivec_be.slaspec
│   │   ├── ppc_64_isa_altivec_le.sla
│   │   ├── ppc_64_isa_altivec_le.slaspec
│   │   ├── ppc_64_isa_altivec_vle_be.sla
│   │   ├── ppc_64_isa_altivec_vle_be.slaspec
│   │   ├── ppc_64_isa_be.sla
│   │   ├── ppc_64_isa_be.slaspec
│   │   ├── ppc_64_isa_le.sla
│   │   ├── ppc_64_isa_le.slaspec
│   │   ├── ppc_64_isa_vle_be.sla
│   │   ├── ppc_64_isa_vle_be.slaspec
│   │   ├── ppc_64_le.cspec
│   │   ├── ppc_64_le.sla
│   │   ├── ppc_64_le.slaspec
│   │   ├── ppc_64.pspec
│   │   ├── ppc_a2.sinc
│   │   ├── ppc_common.sinc
│   │   ├── ppc_embedded.sinc
│   │   ├── ppc_instructions.sinc
│   │   ├── ppc_isa.sinc
│   │   ├── ppc_vle.sinc
│   │   ├── ppc.ldefs
│   │   ├── quicciii.sinc
│   │   ├── Scalar_SPFP.sinc
│   │   ├── SPE_APU.sinc
│   │   ├── SPE_EFSD.sinc
│   │   ├── SPE_EFV.sinc
│   │   ├── SPE_FloatMulAdd.sinc
│   │   ├── SPEF_SCR.sinc
│   │   ├── stmwInstructions.sinc
│   │   ├── stswiInstructions.sinc
│   │   └── vsx.sinc
│   ├── RISCV
│   │   ├── andestar_v5.instr.sinc
│   │   ├── andestar_v5.ldefs
│   │   ├── andestar_v5.sla
│   │   ├── andestar_v5.slaspec
│   │   ├── riscv.csr.sinc
│   │   ├── riscv.custom.sinc
│   │   ├── riscv.ilp32d.sla
│   │   ├── riscv.ilp32d.slaspec
│   │   ├── riscv.instr.sinc
│   │   ├── riscv.ldefs
│   │   ├── riscv.lp64d.sla
│   │   ├── riscv.lp64d.slaspec
│   │   ├── riscv.priv.sinc
│   │   ├── riscv.reg.sinc
│   │   ├── riscv.rv32a.sinc
│   │   ├── riscv.rv32b.sinc
│   │   ├── riscv.rv32d.sinc
│   │   ├── riscv.rv32f.sinc
│   │   ├── riscv.rv32i.sinc
│   │   ├── riscv.rv32k.sinc
│   │   ├── riscv.rv32m.sinc
│   │   ├── riscv.rv32p.sinc
│   │   ├── riscv.rv32q.sinc
│   │   ├── riscv.rv64a.sinc
│   │   ├── riscv.rv64b.sinc
│   │   ├── riscv.rv64d.sinc
│   │   ├── riscv.rv64f.sinc
│   │   ├── riscv.rv64i.sinc
│   │   ├── riscv.rv64k.sinc
│   │   ├── riscv.rv64m.sinc
│   │   ├── riscv.rv64p.sinc
│   │   ├── riscv.rv64q.sinc
│   │   ├── riscv.rvc.sinc
│   │   ├── riscv.rvv.sinc
│   │   ├── riscv.table.sinc
│   │   ├── riscv.zi.sinc
│   │   ├── riscv32-fp.cspec
│   │   ├── riscv32.cspec
│   │   ├── riscv64-fp.cspec
│   │   ├── riscv64.cspec
│   │   ├── RV32.pspec
│   │   └── RV64.pspec
│   ├── Sparc
│   │   ├── SparcV9_32.cspec
│   │   ├── SparcV9_32.sla
│   │   ├── SparcV9_32.slaspec
│   │   ├── SparcV9_64.cspec
│   │   ├── SparcV9_64.sla
│   │   ├── SparcV9_64.slaspec
│   │   ├── SparcV9.ldefs
│   │   ├── SparcV9.pspec
│   │   ├── SparcV9.sinc
│   │   └── SparcVIS.sinc
│   ├── SuperH
│   │   ├── sh-1.sla
│   │   ├── sh-1.slaspec
│   │   ├── sh-2.sla
│   │   ├── sh-2.slaspec
│   │   ├── sh-2a.sla
│   │   ├── sh-2a.slaspec
│   │   ├── superh.cspec
│   │   ├── superh.ldefs
│   │   ├── superh.pspec
│   │   ├── superh.sinc
│   │   └── superh2a.cspec
│   ├── SuperH4
│   │   ├── SuperH4_be.sla
│   │   ├── SuperH4_be.slaspec
│   │   ├── SuperH4_le.sla
│   │   ├── SuperH4_le.slaspec
│   │   ├── SuperH4.ldefs
│   │   └── SuperH4.sinc
│   ├── TI_MSP430
│   │   ├── TI_MSP430.ldefs
│   │   ├── TI_MSP430.sla
│   │   ├── TI_MSP430.slaspec
│   │   ├── TI_MSP430X.sla
│   │   ├── TI_MSP430X.slaspec
│   │   ├── TI430Common.sinc
│   │   └── TI430X.sinc
│   ├── TriCore
│   │   ├── tc172x.pspec
│   │   ├── tc176x.pspec
│   │   ├── tc29x.pspec
│   │   ├── tricore.cspec
│   │   ├── tricore.ldefs
│   │   ├── tricore.pcp.sinc
│   │   ├── tricore.pspec
│   │   ├── tricore.sinc
│   │   ├── tricore.sla
│   │   └── tricore.slaspec
│   ├── V850
│   │   ├── V850_instructions.sinc
│   │   ├── V850.cspec
│   │   ├── V850.ldefs
│   │   ├── V850.pspec
│   │   ├── V850.sinc
│   │   ├── V850.sla
│   │   ├── V850.slaspec
│   │   ├── V850e3.sinc
│   │   ├── V850e3.sla
│   │   └── V850e3.slaspec
│   ├── x86
│   │   ├── adx.sinc
│   │   ├── avx_manual.sinc
│   │   ├── avx.sinc
│   │   ├── avx2_manual.sinc
│   │   ├── avx2.sinc
│   │   ├── avx512_manual.sinc
│   │   ├── avx512.sinc
│   │   ├── bmi1.sinc
│   │   ├── bmi2.sinc
│   │   ├── cet.sinc
│   │   ├── clwb.sinc
│   │   ├── cmpccxadd.sinc
│   │   ├── fma.sinc
│   │   ├── gfni.sinc
│   │   ├── ia.sinc
│   │   ├── lockable.sinc
│   │   ├── lzcnt.sinc
│   │   ├── macros.sinc
│   │   ├── mpx.sinc
│   │   ├── pclmulqdq.sinc
│   │   ├── rao.sinc
│   │   ├── rdrand.sinc
│   │   ├── sgx.sinc
│   │   ├── sha.sinc
│   │   ├── smx.sinc
│   │   ├── x86-16-real.pspec
│   │   ├── x86-16.cspec
│   │   ├── x86-16.pspec
│   │   ├── x86-32-golang.cspec
│   │   ├── x86-64-compat32.pspec
│   │   ├── x86-64-gcc.cspec
│   │   ├── x86-64-golang.cspec
│   │   ├── x86-64-swift.cspec
│   │   ├── x86-64-win.cspec
│   │   ├── x86-64.pspec
│   │   ├── x86-64.sla
│   │   ├── x86-64.slaspec
│   │   ├── x86.ldefs
│   │   ├── x86.pspec
│   │   ├── x86.sla
│   │   ├── x86.slaspec
│   │   ├── x86borland.cspec
│   │   ├── x86delphi.cspec
│   │   ├── x86gcc.cspec
│   │   └── x86win.cspec
│   ├── Xtensa
│   │   ├── cust.sinc
│   │   ├── flix.sinc
│   │   ├── xtensa_be.sla
│   │   ├── xtensa_be.slaspec
│   │   ├── xtensa_depbits.sinc
│   │   ├── xtensa_le.sla
│   │   ├── xtensa_le.slaspec
│   │   ├── xtensa.cspec
│   │   ├── xtensa.ldefs
│   │   ├── xtensa.pspec
│   │   ├── xtensaArch.sinc
│   │   ├── xtensaInstructions.sinc
│   │   └── xtensaMain.sinc
│   └── Z80
│       ├── z180.pspec
│       ├── z180.sla
│       ├── z180.slaspec
│       ├── z182.pspec
│       ├── z80.cspec
│       ├── z80.ldefs
│       ├── z80.pspec
│       ├── z80.sla
│       ├── z80.slaspec
│       └── z8401x.pspec
├── src
│   ├── address
│   │   ├── AbstractAddressSetView.cpp
│   │   ├── Address.cpp
│   │   ├── AddressCollectors.cpp
│   │   ├── AddressIterator.cpp
│   │   ├── AddressIteratorAdapter.cpp
│   │   ├── AddressMapImpl.cpp
│   │   ├── AddressObjectMap.cpp
│   │   ├── AddressRangeImpl.cpp
│   │   ├── AddressRangeIterator.cpp
│   │   ├── AddressRangeSplitter.cpp
│   │   ├── AddressRangeToAddressComparator.cpp
│   │   ├── AddressSet.cpp
│   │   ├── AddressSetCollection.cpp
│   │   ├── AddressSetMapping.cpp
│   │   ├── AddressSetViewAdapter.cpp
│   │   ├── AddressSpace.cpp
│   │   ├── AddressUtils.cpp
│   │   ├── DifferenceAddressSetView.cpp
│   │   ├── EmptyAddressIterator.cpp
│   │   ├── EmptyAddressRangeIterator.cpp
│   │   ├── ImmutableAddressSet.cpp
│   │   ├── IntersectionAddressSetView.cpp
│   │   ├── NormalizedAddressSet.cpp
│   │   ├── ProtectedAddressSpace.cpp
│   │   ├── SegmentedAddress.cpp
│   │   ├── SegmentedAddressSpace.cpp
│   │   ├── SingleAddressSetCollection.cpp
│   │   ├── SpecialAddress.cpp
│   │   ├── SymmetricDifferenceAddressSetView.cpp
│   │   ├── TwoWayBreakdownAddressRangeIterator.cpp
│   │   ├── UnionAddressRangeIterator.cpp
│   │   └── UnionAddressSetView.cpp
│   ├── block
│   │   ├── graph
│   │   │   ├── CodeBlockEdge.cpp
│   │   │   └── CodeBlockVertex.cpp
│   │   ├── BasicBlockModel.cpp
│   │   ├── CodeBlockCache.cpp
│   │   ├── CodeBlockImpl.cpp
│   │   ├── CodeBlockIterator.cpp
│   │   ├── CodeBlockReferenceImpl.cpp
│   │   ├── CodeBlockReferenceIterator.cpp
│   │   ├── ExtCodeBlockImpl.cpp
│   │   ├── FollowFlow.cpp
│   │   ├── IsolatedEntrySubModel.cpp
│   │   ├── MultEntSubIterator.cpp
│   │   ├── MultEntSubModel.cpp
│   │   ├── OverlapCodeSubModel.cpp
│   │   ├── PartitionCodeSubIterator.cpp
│   │   ├── PartitionCodeSubModel.cpp
│   │   ├── SimpleBlockIterator.cpp
│   │   ├── SimpleBlockModel.cpp
│   │   ├── SimpleDestReferenceIterator.cpp
│   │   ├── SimpleSourceReferenceIterator.cpp
│   │   ├── SingleEntSubIterator.cpp
│   │   ├── SubroutineDestReferenceIterator.cpp
│   │   └── SubroutineSourceReferenceIterator.cpp
│   ├── cfg
│   │   ├── DisassemblyCFG.cpp
│   │   └── FunctionGraphLayout.cpp
│   ├── core
│   │   ├── patch
│   │   │   ├── BytePatch.cpp
│   │   │   ├── CodeCaveAllocator.cpp
│   │   │   ├── InstructionPatch.cpp
│   │   │   ├── MetadataPatch.cpp
│   │   │   ├── NopFillPatch.cpp
│   │   │   ├── Patch.cpp
│   │   │   ├── PatchConflictDetector.cpp
│   │   │   ├── PatchGroup.cpp
│   │   │   ├── PatchManager.cpp
│   │   │   ├── PatchMemory.cpp
│   │   │   └── StringPatch.cpp
│   │   ├── AARCH64PltThunkAnalyzer.cpp
│   │   ├── AbstractAnalyzer.cpp
│   │   ├── AbstractBinaryFormatAnalyzer.cpp
│   │   ├── AbstractDemanglerAnalyzer.cpp
│   │   ├── AbstractJavaAnalyzer.cpp
│   │   ├── AddressTableAnalyzer.cpp
│   │   ├── AggressiveInstructionFinderAnalyzer.cpp
│   │   ├── AggressiveRecoveryAnalyzer.cpp
│   │   ├── AnalysisBridge.cpp
│   │   ├── AnalysisPriority.cpp
│   │   ├── AnalysisScheduler.cpp
│   │   ├── AnalysisTaskList.cpp
│   │   ├── Analyzer.cpp
│   │   ├── AndroidBootLoaderAnalyzer.cpp
│   │   ├── Apple8900Analyzer.cpp
│   │   ├── AppleSingleDoubleAnalyzer.cpp
│   │   ├── ApplyDataArchiveAnalyzer.cpp
│   │   ├── ApplyKnownSignatureAnalyzer.cpp
│   │   ├── ArmAggressiveInstructionFinderAnalyzer.cpp
│   │   ├── ArmAnalyzer.cpp
│   │   ├── ArmSymbolAnalyzer.cpp
│   │   ├── ArtAnalyzer.cpp
│   │   ├── Assembler.cpp
│   │   ├── AutoAnalysisManager.cpp
│   │   ├── BinaryLoader.cpp
│   │   ├── BinaryPropertyListAnalyzer.cpp
│   │   ├── BinaryReader.cpp
│   │   ├── BootImageAnalyzer.cpp
│   │   ├── CallFixupAnalyzer.cpp
│   │   ├── CallFixupChangeAnalyzer.cpp
│   │   ├── CategoryPath.cpp
│   │   ├── CFStringAnalyzer.cpp
│   │   ├── CliMetadataTokenAnalyzer.cpp
│   │   ├── CoffAnalyzer.cpp
│   │   ├── CoffArchiveAnalyzer.cpp
│   │   ├── CompilerSpec.cpp
│   │   ├── CondenseFillerBytesAnalyzer.cpp
│   │   ├── ConstantPropagationAnalyzer.cpp
│   │   ├── ConstantPropagationContextEvaluator.cpp
│   │   ├── ContextEvaluatorAdapter.cpp
│   │   ├── CramFsAnalyzer.cpp
│   │   ├── CreateThunkAnalyzer.cpp
│   │   ├── DataOperandReferenceAnalyzer.cpp
│   │   ├── DataOrganization.cpp
│   │   ├── DataRefFunctionAnalyzer.cpp
│   │   ├── DataSectionFunctionScannerAnalyzer.cpp
│   │   ├── DecompilerAdapter.cpp
│   │   ├── DecompilerCallConventionAnalyzer.cpp
│   │   ├── DecompilerFunctionAnalyzer.cpp
│   │   ├── DecompilerSwitchAnalyzer.cpp
│   │   ├── DecompInterface.cpp
│   │   ├── DexCondenseFillerBytesAnalyzer.cpp
│   │   ├── DexExceptionHandlersAnalyzer.cpp
│   │   ├── DexHeaderFormatAnalyzer.cpp
│   │   ├── DexMarkupDataAnalyzer.cpp
│   │   ├── DexMarkupInstructionsAnalyzer.cpp
│   │   ├── DexMarkupSwitchTableAnalyzer.cpp
│   │   ├── Disassembler.cpp
│   │   ├── DisassemblyAnalyzer.cpp
│   │   ├── DmgAnalyzer.cpp
│   │   ├── DtbAnalyzer.cpp
│   │   ├── DWARFAnalyzer.cpp
│   │   ├── DyldCacheAnalyzer.cpp
│   │   ├── eBPFSyscallAnalyzer.cpp
│   │   ├── ElfAnalyzer.cpp
│   │   ├── ElfScalarOperandAnalyzer.cpp
│   │   ├── EmbeddedMediaAnalyzer.cpp
│   │   ├── EntryPointAnalyzer.cpp
│   │   ├── Ext4Analyzer.cpp
│   │   ├── ExternalEntryFunctionAnalyzer.cpp
│   │   ├── ExternalSymbolResolver.cpp
│   │   ├── ExternalSymbolResolverAnalyzer.cpp
│   │   ├── FBPK_Analyzer.cpp
│   │   ├── FdtAnalyzer.cpp
│   │   ├── FidAnalyzer.cpp
│   │   ├── FidHasher.cpp
│   │   ├── FindNoReturnFunctionsAnalyzer.cpp
│   │   ├── FksLibrary.cpp
│   │   ├── FormatStringAnalyzer.cpp
│   │   ├── FragmentMergeAnalyzer.cpp
│   │   ├── FunctionAnalyzer.cpp
│   │   ├── FunctionBodyFinalizer.cpp
│   │   ├── FunctionDiscoveryAnalyzer.cpp
│   │   ├── FunctionDiscoveryAnalyzerAdapter.cpp
│   │   ├── FunctionFingerprint.cpp
│   │   ├── FunctionStartAnalyzer.cpp
│   │   ├── FunctionStartDataPostAnalyzer.cpp
│   │   ├── FunctionStartFuncAnalyzer.cpp
│   │   ├── FunctionStartPostAnalyzer.cpp
│   │   ├── FunctionStartPreFuncAnalyzer.cpp
│   │   ├── GccExceptionAnalyzer.cpp
│   │   ├── GnuDemanglerAnalyzer.cpp
│   │   ├── GoBuildInfoParser.cpp
│   │   ├── GolangStringAnalyzer.cpp
│   │   ├── GolangSymbolAnalyzer.cpp
│   │   ├── GoRttiParser.cpp
│   │   ├── GuardCfgAnalyzer.cpp
│   │   ├── HCS12ConventionAnalyzer.cpp
│   │   ├── HexagonAnalyzer.cpp
│   │   ├── HexagonPrologEpilogAnalyzer.cpp
│   │   ├── HexagonThunkAnalyzer.cpp
│   │   ├── HexagonUnsupportSemanticAnalyzer.cpp
│   │   ├── iBootImAnalyzer.cpp
│   │   ├── Img2Analyzer.cpp
│   │   ├── Img3Analyzer.cpp
│   │   ├── ImportThunkAnalyzer.cpp
│   │   ├── iOS_Analyzer.cpp
│   │   ├── iOS_FixupArmSymbolsAnalyzer.cpp
│   │   ├── iOS_KextStubFixupAnalyzer.cpp
│   │   ├── JavaAnalyzer.cpp
│   │   ├── JvmSwitchAnalyzer.cpp
│   │   ├── KnownFunctionHashes.cpp
│   │   ├── LinuxTypeDatabase.cpp
│   │   ├── LoongsonAnalyzer.cpp
│   │   ├── LzssAnalyzer.cpp
│   │   ├── MachoAnalyzer.cpp
│   │   ├── MachoConstructorDestructorAnalyzer.cpp
│   │   ├── MachoFunctionStartsAnalyzer.cpp
│   │   ├── MacOSTypeDatabase.cpp
│   │   ├── MainRecognitionAnalyzer.cpp
│   │   ├── Memory.cpp
│   │   ├── MemoryBlock.cpp
│   │   ├── MemoryByteProvider.cpp
│   │   ├── MicrosoftDemanglerAnalyzer.cpp
│   │   ├── MingwRelocationAnalyzer.cpp
│   │   ├── MipsAddressAnalyzer.cpp
│   │   ├── MipsPreAnalyzer.cpp
│   │   ├── MipsSymbolAnalyzer.cpp
│   │   ├── Motorola68KAnalyzer.cpp
│   │   ├── Msg.cpp
│   │   ├── MsvcDemangler.cpp
│   │   ├── NamingService.cpp
│   │   ├── NDS32Analyzer.cpp
│   │   ├── NewExt4Analyzer.cpp
│   │   ├── NoReturnFunctionAnalyzer.cpp
│   │   ├── OatExecAnalyzer.cpp
│   │   ├── OatHeaderAnalyzer.cpp
│   │   ├── ObjcMessageAnalyzer.cpp
│   │   ├── ObjcTypeMetadataAnalyzer.cpp
│   │   ├── OdexHeaderFormatAnalyzer.cpp
│   │   ├── OperandReferenceAnalyzer.cpp
│   │   ├── PdbAnalyzer.cpp
│   │   ├── PdbParser.cpp
│   │   ├── PdbUniversalAnalyzer.cpp
│   │   ├── PEExceptionAnalyzer.cpp
│   │   ├── PefAnalyzer.cpp
│   │   ├── PefDebugAnalyzer.cpp
│   │   ├── Pic12Analyzer.cpp
│   │   ├── Pic16Analyzer.cpp
│   │   ├── Pic17c7xxAnalyzer.cpp
│   │   ├── Pic18Analyzer.cpp
│   │   ├── Pic24DInitAnalyzer.cpp
│   │   ├── PicSwitchAnalyzer.cpp
│   │   ├── PortableExecutableAnalyzer.cpp
│   │   ├── PowerPCAddressAnalyzer.cpp
│   │   ├── Program.cpp
│   │   ├── PropagateExternalParametersAnalyzer.cpp
│   │   ├── RefType.cpp
│   │   ├── Register.cpp
│   │   ├── RegisterBuilder.cpp
│   │   ├── RegisterValue.cpp
│   │   ├── RISCVAddressAnalyzer.cpp
│   │   ├── RttiAnalyzer.cpp
│   │   ├── RustDemanglerAnalyzer.cpp
│   │   ├── RustStringAnalyzer.cpp
│   │   ├── ScalarOperandAnalyzer.cpp
│   │   ├── SegmentedCallingConventionAnalyzer.cpp
│   │   ├── SH4AddressAnalyzer.cpp
│   │   ├── SH4EarlyAddressAnalyzer.cpp
│   │   ├── SharedReturnAnalyzer.cpp
│   │   ├── SharedReturnJumpAnalyzer.cpp
│   │   ├── SparcAnalyzer.cpp
│   │   ├── SparcEarlyAddressAnalyzer.cpp
│   │   ├── StackFrameImpl.cpp
│   │   ├── StackReferenceAnalyzer.cpp
│   │   ├── StackReferenceImpl.cpp
│   │   ├── StackVariableAnalyzer.cpp
│   │   ├── StringsAnalyzer.cpp
│   │   ├── SwiftDemanglerAnalyzer.cpp
│   │   ├── SwiftTypeMetadataAnalyzer.cpp
│   │   ├── SymbolicPropogator.cpp
│   │   ├── TaskMonitor.cpp
│   │   ├── TEBAnalyzer.cpp
│   │   ├── ToyAnalyzer.cpp
│   │   ├── TrackedRegisterSeeder.cpp
│   │   ├── TypeDatabaseFactory.cpp
│   │   ├── VarnodeContext.cpp
│   │   ├── VdexHeaderAnalyzer.cpp
│   │   ├── WindowsResourceReferenceAnalyzer.cpp
│   │   ├── WindowsTypeDatabase.cpp
│   │   ├── wintype_siggen.inc
│   │   ├── X86Analyzer.cpp
│   │   └── X86FunctionPurgeAnalyzer.cpp
│   ├── correlate
│   │   ├── AllBytesHashCalculator.cpp
│   │   ├── Block.cpp
│   │   ├── DisambiguateByBytes.cpp
│   │   ├── DisambiguateByChild.cpp
│   │   ├── DisambiguateByParent.cpp
│   │   ├── DisambiguateByParentWithOrder.cpp
│   │   ├── HashedFunctionAddressCorrelation.cpp
│   │   ├── HashEntry.cpp
│   │   ├── HashStore.cpp
│   │   ├── InstructHash.cpp
│   │   ├── MnemonicHashCalculator.cpp
│   │   └── SimpleCRC32.cpp
│   ├── data
│   │   ├── AlignedComponentPacker.cpp
│   │   ├── AlignedStructureInspector.cpp
│   │   ├── AlignedStructurePacker.cpp
│   │   ├── AnnotationHandler.cpp
│   │   ├── BuiltInDataTypeClassExclusionFilter.cpp
│   │   ├── CompositeInternal.cpp
│   │   ├── CycleGroup.cpp
│   │   ├── DataTypeConflictHandler.cpp
│   │   ├── DataTypeManagerChangeListenerHandler.cpp
│   │   ├── DataTypeMerger.cpp
│   │   ├── DataTypeWriter.cpp
│   │   ├── DefaultAnnotationHandler.cpp
│   │   ├── InternalDataTypeComponent.cpp
│   │   └── NoisyStructureBuilder.cpp
│   ├── decompiler
│   │   ├── action.cc
│   │   ├── action.hh
│   │   ├── address.cc
│   │   ├── address.hh
│   │   ├── analyzesigs.cc
│   │   ├── analyzesigs.hh
│   │   ├── architecture.cc
│   │   ├── architecture.hh
│   │   ├── bfd_arch.cc
│   │   ├── bfd_arch.hh
│   │   ├── bitfield.cc
│   │   ├── bitfield.hh
│   │   ├── block.cc
│   │   ├── block.hh
│   │   ├── blockaction.cc
│   │   ├── blockaction.hh
│   │   ├── callgraph.cc
│   │   ├── callgraph.hh
│   │   ├── capability.cc
│   │   ├── capability.hh
│   │   ├── cast.cc
│   │   ├── cast.hh
│   │   ├── CFormatter.cpp
│   │   ├── CFormatter.h
│   │   ├── CMakeLists.txt
│   │   ├── codedata.cc
│   │   ├── codedata.hh
│   │   ├── comment_ghidra.cc
│   │   ├── comment_ghidra.hh
│   │   ├── comment.cc
│   │   ├── comment.hh
│   │   ├── compression.cc
│   │   ├── compression.hh
│   │   ├── condexe.cc
│   │   ├── condexe.hh
│   │   ├── consolemain.cc
│   │   ├── constseq.cc
│   │   ├── constseq.hh
│   │   ├── context.cc
│   │   ├── context.hh
│   │   ├── coreaction.cc
│   │   ├── coreaction.hh
│   │   ├── cover.cc
│   │   ├── cover.hh
│   │   ├── cpool_ghidra.cc
│   │   ├── cpool_ghidra.hh
│   │   ├── cpool.cc
│   │   ├── cpool.hh
│   │   ├── crc32.cc
│   │   ├── crc32.hh
│   │   ├── database_ghidra.cc
│   │   ├── database_ghidra.hh
│   │   ├── database.cc
│   │   ├── database.hh
│   │   ├── doccore.hh
│   │   ├── docmain.hh
│   │   ├── double.cc
│   │   ├── double.hh
│   │   ├── dynamic.cc
│   │   ├── dynamic.hh
│   │   ├── emulate.cc
│   │   ├── emulate.hh
│   │   ├── emulateutil.cc
│   │   ├── emulateutil.hh
│   │   ├── error.hh
│   │   ├── expression.cc
│   │   ├── expression.hh
│   │   ├── filemanage.cc
│   │   ├── filemanage.hh
│   │   ├── float.cc
│   │   ├── float.hh
│   │   ├── flow.cc
│   │   ├── flow.hh
│   │   ├── fspec.cc
│   │   ├── fspec.hh
│   │   ├── funcdata_block.cc
│   │   ├── funcdata_op.cc
│   │   ├── funcdata_varnode.cc
│   │   ├── funcdata.cc
│   │   ├── funcdata.hh
│   │   ├── ghidra_arch.cc
│   │   ├── ghidra_arch.hh
│   │   ├── ghidra_context.cc
│   │   ├── ghidra_context.hh
│   │   ├── ghidra_process.cc
│   │   ├── ghidra_process.hh
│   │   ├── ghidra_translate.cc
│   │   ├── ghidra_translate.hh
│   │   ├── globalcontext.cc
│   │   ├── globalcontext.hh
│   │   ├── grammar.cc
│   │   ├── grammar.hh
│   │   ├── grammar.y
│   │   ├── graph.cc
│   │   ├── graph.hh
│   │   ├── heritage.cc
│   │   ├── heritage.hh
│   │   ├── ifacedecomp.cc
│   │   ├── ifacedecomp.hh
│   │   ├── ifaceterm.cc
│   │   ├── ifaceterm.hh
│   │   ├── inject_ghidra.cc
│   │   ├── inject_ghidra.hh
│   │   ├── inject_sleigh.cc
│   │   ├── inject_sleigh.hh
│   │   ├── interface.cc
│   │   ├── interface.hh
│   │   ├── jumptable.cc
│   │   ├── jumptable.hh
│   │   ├── libdecomp.cc
│   │   ├── libdecomp.hh
│   │   ├── loadimage_bfd.cc
│   │   ├── loadimage_bfd.hh
│   │   ├── loadimage_ghidra.cc
│   │   ├── loadimage_ghidra.hh
│   │   ├── loadimage_xml.cc
│   │   ├── loadimage_xml.hh
│   │   ├── loadimage.cc
│   │   ├── loadimage.hh
│   │   ├── marshal.cc
│   │   ├── marshal.hh
│   │   ├── memstate.cc
│   │   ├── memstate.hh
│   │   ├── merge.cc
│   │   ├── merge.hh
│   │   ├── modelrules.cc
│   │   ├── modelrules.hh
│   │   ├── multiprecision.cc
│   │   ├── multiprecision.hh
│   │   ├── op.cc
│   │   ├── op.hh
│   │   ├── opbehavior.cc
│   │   ├── opbehavior.hh
│   │   ├── opcodes.cc
│   │   ├── opcodes.hh
│   │   ├── options.cc
│   │   ├── options.hh
│   │   ├── override.cc
│   │   ├── override.hh
│   │   ├── paramid.cc
│   │   ├── paramid.hh
│   │   ├── partmap.hh
│   │   ├── pcodecompile.cc
│   │   ├── pcodecompile.hh
│   │   ├── pcodeinject.cc
│   │   ├── pcodeinject.hh
│   │   ├── pcodeparse.cc
│   │   ├── pcodeparse.hh
│   │   ├── pcodeparse.y
│   │   ├── pcoderaw.cc
│   │   ├── pcoderaw.hh
│   │   ├── prefersplit.cc
│   │   ├── prefersplit.hh
│   │   ├── prettyprint.cc
│   │   ├── prettyprint.hh
│   │   ├── printc.cc
│   │   ├── printc.hh
│   │   ├── printjava.cc
│   │   ├── printjava.hh
│   │   ├── printlanguage.cc
│   │   ├── printlanguage.hh
│   │   ├── rangemap.hh
│   │   ├── rangeutil.cc
│   │   ├── rangeutil.hh
│   │   ├── raw_arch.cc
│   │   ├── raw_arch.hh
│   │   ├── ruleaction.cc
│   │   ├── ruleaction.hh
│   │   ├── rulecompile.cc
│   │   ├── rulecompile.hh
│   │   ├── ruleparse.y
│   │   ├── semantics.cc
│   │   ├── semantics.hh
│   │   ├── signature_ghidra.cc
│   │   ├── signature_ghidra.hh
│   │   ├── signature.cc
│   │   ├── signature.hh
│   │   ├── slaformat.cc
│   │   ├── slaformat.hh
│   │   ├── sleigh_arch.cc
│   │   ├── sleigh_arch.hh
│   │   ├── sleigh.cc
│   │   ├── sleigh.hh
│   │   ├── sleighbase.cc
│   │   ├── sleighbase.hh
│   │   ├── sleighexample.cc
│   │   ├── slgh_compile.cc
│   │   ├── slgh_compile.hh
│   │   ├── slghparse.cc
│   │   ├── slghparse.hh
│   │   ├── slghparse.y
│   │   ├── slghpatexpress.cc
│   │   ├── slghpatexpress.hh
│   │   ├── slghpattern.cc
│   │   ├── slghpattern.hh
│   │   ├── slghscan.cc
│   │   ├── slghscan.l
│   │   ├── slghsymbol.cc
│   │   ├── slghsymbol.hh
│   │   ├── space.cc
│   │   ├── space.hh
│   │   ├── string_ghidra.cc
│   │   ├── string_ghidra.hh
│   │   ├── stringmanage.cc
│   │   ├── stringmanage.hh
│   │   ├── subflow.cc
│   │   ├── subflow.hh
│   │   ├── test.cc
│   │   ├── test.hh
│   │   ├── testfunction.cc
│   │   ├── testfunction.hh
│   │   ├── transform.cc
│   │   ├── transform.hh
│   │   ├── translate.cc
│   │   ├── translate.hh
│   │   ├── type.cc
│   │   ├── type.hh
│   │   ├── typegrp_ghidra.cc
│   │   ├── typegrp_ghidra.hh
│   │   ├── typeop.cc
│   │   ├── typeop.hh
│   │   ├── types.h
│   │   ├── unify.cc
│   │   ├── unify.hh
│   │   ├── unionresolve.cc
│   │   ├── unionresolve.hh
│   │   ├── userop.cc
│   │   ├── userop.hh
│   │   ├── variable.cc
│   │   ├── variable.hh
│   │   ├── varmap.cc
│   │   ├── varmap.hh
│   │   ├── varnode.cc
│   │   ├── varnode.hh
│   │   ├── xml_arch.cc
│   │   ├── xml_arch.hh
│   │   ├── xml.cc
│   │   ├── xml.hh
│   │   └── xml.y
│   ├── exceptions
│   │   └── VersionException.cpp
│   ├── function
│   │   ├── Function.cpp
│   │   ├── FunctionManager.cpp
│   │   └── Variable.cpp
│   ├── gclass
│   │   ├── ClassID.cpp
│   │   └── ClassUtils.cpp
│   ├── gui
│   │   ├── icons
│   │   │   ├── app_icon.png
│   │   │   ├── donate.svg
│   │   │   ├── export.svg
│   │   │   ├── folder-free.svg
│   │   │   ├── folder-open.svg
│   │   │   ├── function.svg
│   │   │   ├── help.svg
│   │   │   ├── import.svg
│   │   │   ├── segment.svg
│   │   │   ├── settings.svg
│   │   │   ├── shield.svg
│   │   │   ├── string.svg
│   │   │   ├── symbol.svg
│   │   │   └── type.svg
│   │   ├── AddressMinimap.cpp
│   │   ├── AddressMinimap.h
│   │   ├── CodePlainTextEdit.cpp
│   │   ├── CodePlainTextEdit.h
│   │   ├── CommandPaletteDialog.cpp
│   │   ├── CommandPaletteDialog.h
│   │   ├── ConsoleWidget.cpp
│   │   ├── ConsoleWidget.h
│   │   ├── CppHighlighter.cpp
│   │   ├── CppHighlighter.h
│   │   ├── CrossReferenceExplorer.cpp
│   │   ├── CrossReferenceExplorer.h
│   │   ├── DecompilerView.cpp
│   │   ├── DecompilerView.h
│   │   ├── DisasmSearchBar.cpp
│   │   ├── DisasmSearchBar.h
│   │   ├── DisassemblyFieldView.cpp
│   │   ├── DisassemblyFieldView.h
│   │   ├── DisassemblyModel.cpp
│   │   ├── DisassemblyModel.h
│   │   ├── DyldCacheBrowserDialog.cpp
│   │   ├── DyldCacheBrowserDialog.h
│   │   ├── EditorTheme.cpp
│   │   ├── EditorTheme.h
│   │   ├── FieldView.cpp
│   │   ├── FieldView.h
│   │   ├── FunctionExplorer.cpp
│   │   ├── FunctionExplorer.h
│   │   ├── FunctionGraphView.cpp
│   │   ├── FunctionGraphView.h
│   │   ├── FunctionGraphWindow.cpp
│   │   ├── FunctionGraphWindow.h
│   │   ├── GuiConflictHandler.cpp
│   │   ├── GuiConflictHandler.h
│   │   ├── HexSearchBar.cpp
│   │   ├── HexSearchBar.h
│   │   ├── HexView.cpp
│   │   ├── HexView.h
│   │   ├── main.cpp
│   │   ├── MainWindow.cpp
│   │   ├── MainWindow.h
│   │   ├── PatchListWidget.cpp
│   │   ├── PatchListWidget.h
│   │   ├── resources.qrc
│   │   ├── SelectionManager.cpp
│   │   ├── SelectionManager.h
│   │   ├── SelectionState.h
│   │   ├── StatusBarWidget.cpp
│   │   ├── StatusBarWidget.h
│   │   ├── StringTableWidget.cpp
│   │   ├── StringTableWidget.h
│   │   ├── StructureEditorWidget.cpp
│   │   ├── StructureEditorWidget.h
│   │   ├── TypeConflictDialog.cpp
│   │   └── TypeConflictDialog.h
│   ├── import
│   │   ├── GbfReader.cpp
│   │   ├── GzfProgramImporter.cpp
│   │   ├── RepProject.cpp
│   │   ├── ZipArchive.cpp
│   │   └── ZipArchive.h
│   ├── include
│   │   ├── cfg
│   │   │   ├── DisassemblyCFG.h
│   │   │   └── FunctionGraphLayout.h
│   │   ├── ghidra
│   │   │   ├── block
│   │   │   │   ├── graph
│   │   │   │   │   ├── CodeBlockEdge.h
│   │   │   │   │   └── CodeBlockVertex.h
│   │   │   │   ├── BasicBlockModel.h
│   │   │   │   ├── CodeBlock.h
│   │   │   │   ├── CodeBlockCache.h
│   │   │   │   ├── CodeBlockImpl.h
│   │   │   │   ├── CodeBlockIterator.h
│   │   │   │   ├── CodeBlockModel.h
│   │   │   │   ├── CodeBlockReference.h
│   │   │   │   ├── CodeBlockReferenceImpl.h
│   │   │   │   ├── CodeBlockReferenceIterator.h
│   │   │   │   ├── ExtCodeBlockImpl.h
│   │   │   │   ├── FollowFlow.h
│   │   │   │   ├── IsolatedEntrySubModel.h
│   │   │   │   ├── MultEntSubIterator.h
│   │   │   │   ├── MultEntSubModel.h
│   │   │   │   ├── OverlapCodeSubModel.h
│   │   │   │   ├── PartitionCodeSubIterator.h
│   │   │   │   ├── PartitionCodeSubModel.h
│   │   │   │   ├── SimpleBlockIterator.h
│   │   │   │   ├── SimpleBlockModel.h
│   │   │   │   ├── SimpleDestReferenceIterator.h
│   │   │   │   ├── SimpleSourceReferenceIterator.h
│   │   │   │   ├── SingleEntSubIterator.h
│   │   │   │   ├── SubroutineBlockModel.h
│   │   │   │   ├── SubroutineDestReferenceIterator.h
│   │   │   │   └── SubroutineSourceReferenceIterator.h
│   │   │   ├── correlate
│   │   │   │   ├── AllBytesHashCalculator.h
│   │   │   │   ├── Block.h
│   │   │   │   ├── DisambiguateByBytes.h
│   │   │   │   ├── DisambiguateByChild.h
│   │   │   │   ├── DisambiguateByParent.h
│   │   │   │   ├── DisambiguateByParentWithOrder.h
│   │   │   │   ├── DisambiguateStrategy.h
│   │   │   │   ├── Hash.h
│   │   │   │   ├── HashCalculator.h
│   │   │   │   ├── HashedFunctionAddressCorrelation.h
│   │   │   │   ├── HashEntry.h
│   │   │   │   ├── HashStore.h
│   │   │   │   ├── InstructHash.h
│   │   │   │   └── MnemonicHashCalculator.h
│   │   │   ├── import
│   │   │   │   ├── GbfReader.h
│   │   │   │   ├── GzfProgramImporter.h
│   │   │   │   └── RepProject.h
│   │   │   ├── patch
│   │   │   │   ├── BytePatch.h
│   │   │   │   ├── CodeCaveAllocator.h
│   │   │   │   ├── InstructionPatch.h
│   │   │   │   ├── MetadataPatch.h
│   │   │   │   ├── NopFillPatch.h
│   │   │   │   ├── Patch.h
│   │   │   │   ├── PatchConflictDetector.h
│   │   │   │   ├── PatchGroup.h
│   │   │   │   ├── PatchManager.h
│   │   │   │   ├── PatchMemory.h
│   │   │   │   └── StringPatch.h
│   │   │   ├── pcode
│   │   │   │   ├── CodeBlock.h
│   │   │   │   ├── CodeBlockImpl.h
│   │   │   │   ├── CodeBlockIterator.h
│   │   │   │   ├── CodeBlockModel.h
│   │   │   │   ├── CodeBlockReference.h
│   │   │   │   ├── CodeBlockReferenceImpl.h
│   │   │   │   ├── CodeBlockReferenceIterator.h
│   │   │   │   ├── EquateSymbol.h
│   │   │   │   ├── ExtCodeBlockImpl.h
│   │   │   │   ├── FunctionPrototype.h
│   │   │   │   ├── HighCodeSymbol.h
│   │   │   │   ├── HighConstant.h
│   │   │   │   ├── HighExternalSymbol.h
│   │   │   │   ├── HighFunction.h
│   │   │   │   ├── HighFunctionDBUtil.h
│   │   │   │   ├── HighFunctionShellSymbol.h
│   │   │   │   ├── HighFunctionSymbol.h
│   │   │   │   ├── HighGlobal.h
│   │   │   │   ├── HighLabelSymbol.h
│   │   │   │   ├── HighLocal.h
│   │   │   │   ├── HighOther.h
│   │   │   │   ├── HighParam.h
│   │   │   │   ├── HighParamID.h
│   │   │   │   ├── HighVariable.h
│   │   │   │   ├── JumpTable.h
│   │   │   │   ├── ParamMeasure.h
│   │   │   │   └── PcodeException.h
│   │   │   ├── program
│   │   │   │   └── model
│   │   │   │       ├── data
│   │   │   │       └── symbol
│   │   │   ├── storage
│   │   │   │   ├── BranchManager.h
│   │   │   │   ├── CommitManager.h
│   │   │   │   ├── Event.h
│   │   │   │   ├── EventLog.h
│   │   │   │   ├── FksIndexManager.h
│   │   │   │   ├── FksRepository.h
│   │   │   │   ├── IndexManager.h
│   │   │   │   ├── Repository.h
│   │   │   │   ├── SnapshotReader.h
│   │   │   │   ├── SnapshotWriter.h
│   │   │   │   └── WorkingSnapshot.h
│   │   │   ├── util
│   │   │   │   └── datastruct
│   │   │   │       ├── Accumulator.h
│   │   │   │       ├── IndexRange.h
│   │   │   │       ├── IndexRangeIterator.h
│   │   │   │       ├── ListAccumulator.h
│   │   │   │       ├── Range.h
│   │   │   │       ├── RedBlackEntry.h
│   │   │   │       ├── RedBlackTree.h
│   │   │   │       ├── SetAccumulator.h
│   │   │   │       └── SortedRangeList.h
│   │   │   ├── AARCH64PltThunkAnalyzer.h
│   │   │   ├── AbstractAddressSetView.h
│   │   │   ├── AbstractAnalyzer.h
│   │   │   ├── AbstractBinaryFormatAnalyzer.h
│   │   │   ├── AbstractColorDataType.h
│   │   │   ├── AbstractComplexDataType.h
│   │   │   ├── AbstractDataType.h
│   │   │   ├── AbstractDemanglerAnalyzer.h
│   │   │   ├── AbstractDependencyGraph.h
│   │   │   ├── AbstractFloatDataType.h
│   │   │   ├── AbstractIntegerDataType.h
│   │   │   ├── AbstractJavaAnalyzer.h
│   │   │   ├── AbstractLeb128DataType.h
│   │   │   ├── AbstractPointerTypedefBuiltIn.h
│   │   │   ├── AbstractSignedIntegerDataType.h
│   │   │   ├── AbstractStringDataType.h
│   │   │   ├── AbstractUnsignedIntegerDataType.h
│   │   │   ├── AccessPcodeExecutionException.h
│   │   │   ├── AccumulatorSizeException.h
│   │   │   ├── Action.h
│   │   │   ├── ActionManager.h
│   │   │   ├── AcyclicCallGraphBuilder.h
│   │   │   ├── Address.h
│   │   │   ├── AddressChangeSet.h
│   │   │   ├── AddressCollectors.h
│   │   │   ├── AddressFactory.h
│   │   │   ├── AddressFormatException.h
│   │   │   ├── AddressHash.h
│   │   │   ├── AddressIterator.h
│   │   │   ├── AddressIteratorAdapter.h
│   │   │   ├── AddressLabelInfo.h
│   │   │   ├── AddressLabelPair.h
│   │   │   ├── AddressMap.h
│   │   │   ├── AddressMapImpl.h
│   │   │   ├── AddressObjectMap.h
│   │   │   ├── AddressOutOfBoundsException.h
│   │   │   ├── AddressOverflowException.h
│   │   │   ├── AddressRange.h
│   │   │   ├── AddressRangeChunker.h
│   │   │   ├── AddressRangeImpl.h
│   │   │   ├── AddressRangeIterator.h
│   │   │   ├── AddressRangeSplitter.h
│   │   │   ├── AddressRangeToAddressComparator.h
│   │   │   ├── AddressRangeVectorIterator.h
│   │   │   ├── AddressSet.h
│   │   │   ├── AddressSetCollection.h
│   │   │   ├── AddressSetMapping.h
│   │   │   ├── AddressSetPropertyMap.h
│   │   │   ├── AddressSetView.h
│   │   │   ├── AddressSetViewAdapter.h
│   │   │   ├── AddressSpace.h
│   │   │   ├── AddressSpaceSettingsDefinition.h
│   │   │   ├── AddressTableAnalyzer.h
│   │   │   ├── AddressTranslationException.h
│   │   │   ├── AddressUtils.h
│   │   │   ├── AddressXML.h
│   │   │   ├── AddrSpace.h
│   │   │   ├── AggressiveInstructionFinderAnalyzer.h
│   │   │   ├── AggressiveRecoveryAnalyzer.h
│   │   │   ├── AIFFDataType.h
│   │   │   ├── AlignedComponentPacker.h
│   │   │   ├── AlignedStructureInspector.h
│   │   │   ├── AlignedStructurePacker.h
│   │   │   ├── AlignmentDataType.h
│   │   │   ├── AlignmentType.h
│   │   │   ├── AnalysisBridge.h
│   │   │   ├── AnalysisOptionsUpdater.h
│   │   │   ├── AnalysisPriority.h
│   │   │   ├── AnalysisScheduler.h
│   │   │   ├── AnalysisTaskList.h
│   │   │   ├── AnalysisWorker.h
│   │   │   ├── Analyzer.h
│   │   │   ├── AnalyzerAdapter.h
│   │   │   ├── AndFilter.h
│   │   │   ├── AndQuery.h
│   │   │   ├── AndroidBootLoaderAnalyzer.h
│   │   │   ├── AnnotationException.h
│   │   │   ├── AnnotationHandler.h
│   │   │   ├── Apple8900Analyzer.h
│   │   │   ├── AppleSingleDoubleAnalyzer.h
│   │   │   ├── ApplyDataArchiveAnalyzer.h
│   │   │   ├── ApplyKnownSignatureAnalyzer.h
│   │   │   ├── Architecture.h
│   │   │   ├── ArchiveType.h
│   │   │   ├── ArmAggressiveInstructionFinderAnalyzer.h
│   │   │   ├── ArmAnalyzer.h
│   │   │   ├── ArmSymbolAnalyzer.h
│   │   │   ├── Array.h
│   │   │   ├── ArrayDataType.h
│   │   │   ├── ArrayStringable.h
│   │   │   ├── ArtAnalyzer.h
│   │   │   ├── Assembler.h
│   │   │   ├── AssemblyError.h
│   │   │   ├── AssemblyException.h
│   │   │   ├── AssemblyGrammarException.h
│   │   │   ├── AssemblySemanticException.h
│   │   │   ├── AssemblySyntaxException.h
│   │   │   ├── AssertException.h
│   │   │   ├── AssignAction.h
│   │   │   ├── AttributeId.h
│   │   │   ├── AUDataType.h
│   │   │   ├── AudioPlayer.h
│   │   │   ├── AutoAnalysisManager.h
│   │   │   ├── AutoAnalysisManagerListener.h
│   │   │   ├── AutoNaming.h
│   │   │   ├── AutoParameterImpl.h
│   │   │   ├── AutoParameterType.h
│   │   │   ├── BadDataType.h
│   │   │   ├── BadLinkException.h
│   │   │   ├── BadSchemaException.h
│   │   │   ├── BailoutException.h
│   │   │   ├── BasicCompilerSpec.h
│   │   │   ├── BasicCompilerSpecDescription.h
│   │   │   ├── BasicLanguageDescription.h
│   │   │   ├── BinaryLoader.h
│   │   │   ├── BinaryPropertyListAnalyzer.h
│   │   │   ├── BinaryReader.h
│   │   │   ├── BitFieldDataType.h
│   │   │   ├── BitFieldPacking.h
│   │   │   ├── BitFieldPackingImpl.h
│   │   │   ├── BitGroup.h
│   │   │   ├── BitmapResource.h
│   │   │   ├── BitmapResourceDataType.h
│   │   │   ├── BlockGraph.h
│   │   │   ├── Bookmark.h
│   │   │   ├── BookmarkComparator.h
│   │   │   ├── BookmarkManager.h
│   │   │   ├── BookmarkManagerImpl.h
│   │   │   ├── BookmarkType.h
│   │   │   ├── BookmarkTypeComparator.h
│   │   │   ├── BooleanDataType.h
│   │   │   ├── BooleanSettingsDefinition.h
│   │   │   ├── BootImageAnalyzer.h
│   │   │   ├── BootstrapInfoException.h
│   │   │   ├── BuiltIn.h
│   │   │   ├── BuiltInDataType.h
│   │   │   ├── BuiltInDataTypeClassExclusionFilter.h
│   │   │   ├── BuiltInDataTypeManager.h
│   │   │   ├── BusyToolException.h
│   │   │   ├── ByteBlockAccessException.h
│   │   │   ├── ByteDataType.h
│   │   │   ├── ByteIngest.h
│   │   │   ├── ByteMemBufferImpl.h
│   │   │   ├── ByteProvider.h
│   │   │   ├── CachedEncoder.h
│   │   │   ├── CallFixupAnalyzer.h
│   │   │   ├── CallFixupChangeAnalyzer.h
│   │   │   ├── CancelledException.h
│   │   │   ├── CancelledSQLException.h
│   │   │   ├── CartConfigurationException.h
│   │   │   ├── CartInvalidARC4KeyException.h
│   │   │   ├── CartInvalidCartException.h
│   │   │   ├── Category.h
│   │   │   ├── CategoryPath.h
│   │   │   ├── CFStringAnalyzer.h
│   │   │   ├── ChangeSet.h
│   │   │   ├── CharDataType.h
│   │   │   ├── CharsetInfo.h
│   │   │   ├── CharsetInfoManager.h
│   │   │   ├── CharsetSettingsDefinition.h
│   │   │   ├── CircularDependencyException.h
│   │   │   ├── ClassID.h
│   │   │   ├── ClassUtils.h
│   │   │   ├── CliMetadataTokenAnalyzer.h
│   │   │   ├── ClosedException.h
│   │   │   ├── CodeManager.h
│   │   │   ├── CodeUnit.h
│   │   │   ├── CodeUnitComments.h
│   │   │   ├── CodeUnitInsertionException.h
│   │   │   ├── CodeUnitIterator.h
│   │   │   ├── CoffAnalyzer.h
│   │   │   ├── CoffArchiveAnalyzer.h
│   │   │   ├── CoffException.h
│   │   │   ├── ColorIcon.h
│   │   │   ├── Comment.h
│   │   │   ├── CommentHistory.h
│   │   │   ├── CommentType.h
│   │   │   ├── CompilerSpec.h
│   │   │   ├── CompilerSpecDescription.h
│   │   │   ├── CompilerSpecID.h
│   │   │   ├── CompilerSpecNotFoundException.h
│   │   │   ├── Complex16DataType.h
│   │   │   ├── Complex32DataType.h
│   │   │   ├── Complex8DataType.h
│   │   │   ├── ComponentOffsetSettingsDefinition.h
│   │   │   ├── Composite.h
│   │   │   ├── CompositeAlignmentHelper.h
│   │   │   ├── CompositeDataTypeImpl.h
│   │   │   ├── CompositeInternal.h
│   │   │   ├── CondenseFillerBytesAnalyzer.h
│   │   │   ├── ConstantPool.h
│   │   │   ├── ConstantPropagationAnalyzer.h
│   │   │   ├── ConstantPropagationContextEvaluator.h
│   │   │   ├── Constructor.h
│   │   │   ├── ConstructState.h
│   │   │   ├── ConsumeAs.h
│   │   │   ├── ConsumeExtra.h
│   │   │   ├── ConsumeRemaining.h
│   │   │   ├── ContextChangeException.h
│   │   │   ├── ContextDatabase.h
│   │   │   ├── ContextEvaluator.h
│   │   │   ├── ContextEvaluatorAdapter.h
│   │   │   ├── ContextField.h
│   │   │   ├── ContextSetting.h
│   │   │   ├── ContextSymbol.h
│   │   │   ├── ConvertToPointer.h
│   │   │   ├── CountedDynamicDataType.h
│   │   │   ├── CountLatch.h
│   │   │   ├── Cover.h
│   │   │   ├── CramFsAnalyzer.h
│   │   │   ├── CreateThunkAnalyzer.h
│   │   │   ├── CryptoException.h
│   │   │   ├── CustomFormat.h
│   │   │   ├── CustomOrganization.h
│   │   │   ├── CycleGroup.h
│   │   │   ├── Data.h
│   │   │   ├── Database.h
│   │   │   ├── DatabaseAdapter.h
│   │   │   ├── DatabaseVersionException.h
│   │   │   ├── DataBuffer.h
│   │   │   ├── DataConverter.h
│   │   │   ├── DataDirectoryException.h
│   │   │   ├── DataImage.h
│   │   │   ├── DataIterator.h
│   │   │   ├── DataOperandReferenceAnalyzer.h
│   │   │   ├── DataOrganization.h
│   │   │   ├── DataOrganizationImpl.h
│   │   │   ├── DataRefFunctionAnalyzer.h
│   │   │   ├── DataRefType.h
│   │   │   ├── DataSectionFunctionScannerAnalyzer.h
│   │   │   ├── DataStub.h
│   │   │   ├── DataType.h
│   │   │   ├── DataTypeArchive.h
│   │   │   ├── DataTypeArchiveChangeSet.h
│   │   │   ├── DataTypeArchiveIdDumper.h
│   │   │   ├── DataTypeArchiveImpl.h
│   │   │   ├── DataTypeChangeSet.h
│   │   │   ├── DataTypeComparator.h
│   │   │   ├── DataTypeComponent.h
│   │   │   ├── DataTypeComponentImpl.h
│   │   │   ├── DataTypeConflictHandler.h
│   │   │   ├── DataTypeDependencyException.h
│   │   │   ├── DataTypeDisplayOptions.h
│   │   │   ├── DataTypeEncodeException.h
│   │   │   ├── DatatypeFilter.h
│   │   │   ├── DataTypeImpl.h
│   │   │   ├── DataTypeInfo.h
│   │   │   ├── DataTypeInstance.h
│   │   │   ├── DataTypeManager.h
│   │   │   ├── DataTypeManagerChangeListener.h
│   │   │   ├── DataTypeManagerChangeListenerAdapter.h
│   │   │   ├── DataTypeManagerChangeListenerHandler.h
│   │   │   ├── DataTypeManagerDomainObject.h
│   │   │   ├── DataTypeManagerImpl.h
│   │   │   ├── DatatypeMatchFilter.h
│   │   │   ├── DataTypeMergeException.h
│   │   │   ├── DataTypeMerger.h
│   │   │   ├── DataTypeMnemonicSettingsDefinition.h
│   │   │   ├── DataTypeNameComparator.h
│   │   │   ├── DataTypeObjectComparator.h
│   │   │   ├── DataTypePath.h
│   │   │   ├── DataTypeProviderContext.h
│   │   │   ├── DataTypeSymbol.h
│   │   │   ├── DataTypeTransferable.h
│   │   │   ├── DataTypeUtilities.h
│   │   │   ├── DataTypeWithCharset.h
│   │   │   ├── DataTypeWriter.h
│   │   │   ├── DataUtilities.h
│   │   │   ├── DBRollbackException.h
│   │   │   ├── DecisionNode.h
│   │   │   ├── DecodePcodeExecutionException.h
│   │   │   ├── Decoder.h
│   │   │   ├── DecoderException.h
│   │   │   ├── DecompileException.h
│   │   │   ├── DecompilerAdapter.h
│   │   │   ├── DecompilerCallConventionAnalyzer.h
│   │   │   ├── DecompilerFunctionAnalyzer.h
│   │   │   ├── DecompilerLanguage.h
│   │   │   ├── DecompilerSwitchAnalyzer.h
│   │   │   ├── DecompInterface.h
│   │   │   ├── DefaultAddressFactory.h
│   │   │   ├── DefaultAnnotationHandler.h
│   │   │   ├── DefaultDataType.h
│   │   │   ├── DefaultIntPropertyMap.h
│   │   │   ├── DefaultProgramContext.h
│   │   │   ├── DefaultPropertyMap.h
│   │   │   ├── DeletedException.h
│   │   │   ├── DemangledException.h
│   │   │   ├── DemanglerParseException.h
│   │   │   ├── DependencyGraph.h
│   │   │   ├── DepthFirstSearch.h
│   │   │   ├── DexCondenseFillerBytesAnalyzer.h
│   │   │   ├── DexExceptionHandlersAnalyzer.h
│   │   │   ├── DexHeaderFormatAnalyzer.h
│   │   │   ├── DexMarkupDataAnalyzer.h
│   │   │   ├── DexMarkupInstructionsAnalyzer.h
│   │   │   ├── DexMarkupSwitchTableAnalyzer.h
│   │   │   ├── DialogResourceDataType.h
│   │   │   ├── DifferenceAddressSetView.h
│   │   │   ├── DirectedGraph.h
│   │   │   ├── Disassembler.h
│   │   │   ├── DisassemblerContext.h
│   │   │   ├── DisassemblerContextAdapter.h
│   │   │   ├── DisassemblyAnalyzer.h
│   │   │   ├── Disposable.h
│   │   │   ├── DisposedException.h
│   │   │   ├── DmgAnalyzer.h
│   │   │   ├── DomainFileBasedDataTypeManager.h
│   │   │   ├── DomainObjectChangeSet.h
│   │   │   ├── DomainObjectException.h
│   │   │   ├── DomainObjectLockedException.h
│   │   │   ├── Dominator.h
│   │   │   ├── DoubleComplexDataType.h
│   │   │   ├── DoubleDataType.h
│   │   │   ├── DtbAnalyzer.h
│   │   │   ├── DumbMemBufferImpl.h
│   │   │   ├── DummySourceFileManager.h
│   │   │   ├── Duo.h
│   │   │   ├── DuplicateFileException.h
│   │   │   ├── DuplicateGroupException.h
│   │   │   ├── DuplicateIdException.h
│   │   │   ├── DuplicateKeyException.h
│   │   │   ├── DuplicateNameException.h
│   │   │   ├── DWARFAnalyzer.h
│   │   │   ├── DWARFException.h
│   │   │   ├── DWARFExpressionException.h
│   │   │   ├── DWARFExpressionTerminalDerefException.h
│   │   │   ├── DWARFExpressionUnsupportedOpException.h
│   │   │   ├── DWARFExpressionValueException.h
│   │   │   ├── DWARFLineException.h
│   │   │   ├── DWordDataType.h
│   │   │   ├── DyldCacheAnalyzer.h
│   │   │   ├── Dynamic.h
│   │   │   ├── DynamicDataType.h
│   │   │   ├── DynamicEntry.h
│   │   │   ├── DynamicHash.h
│   │   │   ├── DynamicReference.h
│   │   │   ├── DynamicVariableStorage.h
│   │   │   ├── eBPFSyscallAnalyzer.h
│   │   │   ├── Edge.h
│   │   │   ├── ElasticException.h
│   │   │   ├── ElementId.h
│   │   │   ├── ElfAnalyzer.h
│   │   │   ├── ElfException.h
│   │   │   ├── ElfScalarOperandAnalyzer.h
│   │   │   ├── EmbeddedMediaAnalyzer.h
│   │   │   ├── EmptyAddressIterator.h
│   │   │   ├── EmptyAddressRangeIterator.h
│   │   │   ├── EmptyCompositeException.h
│   │   │   ├── EmuInvalidSystemCallException.h
│   │   │   ├── EmuIOException.h
│   │   │   ├── Emulate.h
│   │   │   ├── EmuProcessExitedException.h
│   │   │   ├── EmuSystemException.h
│   │   │   ├── EmuUnixException.h
│   │   │   ├── Encoder.h
│   │   │   ├── Endian.h
│   │   │   ├── EndianSettingsDefinition.h
│   │   │   ├── EnigmaPipeline.h
│   │   │   ├── EntryPointAnalyzer.h
│   │   │   ├── EntryPointReference.h
│   │   │   ├── Enum.h
│   │   │   ├── EnumDataType.h
│   │   │   ├── EnumSettingsDefinition.h
│   │   │   ├── EnumSignedState.h
│   │   │   ├── EnumValuePartitioner.h
│   │   │   ├── EquateReference.h
│   │   │   ├── EquateTable.h
│   │   │   ├── EquateTableImpl.h
│   │   │   ├── ExceptionHandlerFrameException.h
│   │   │   ├── ExclusiveCheckoutException.h
│   │   │   ├── ExporterException.h
│   │   │   ├── ExpressionException.h
│   │   │   ├── Ext4Analyzer.h
│   │   │   ├── ExtensionPoint.h
│   │   │   ├── ExternalEntryFunctionAnalyzer.h
│   │   │   ├── ExternalLanguageCompilerSpecQuery.h
│   │   │   ├── ExternalLocation.h
│   │   │   ├── ExternalLocationAdapter.h
│   │   │   ├── ExternalLocationIterator.h
│   │   │   ├── ExternalManager.h
│   │   │   ├── ExternalManagerImpl.h
│   │   │   ├── ExternalPath.h
│   │   │   ├── ExternalReference.h
│   │   │   ├── ExternalSymbolResolver.h
│   │   │   ├── ExternalSymbolResolverAnalyzer.h
│   │   │   ├── ExtraStack.h
│   │   │   ├── FactoryDataType.h
│   │   │   ├── FactoryStructureDataType.h
│   │   │   ├── FailedToStartGhidraException.h
│   │   │   ├── FBPK_Analyzer.h
│   │   │   ├── FdtAnalyzer.h
│   │   │   ├── FidAnalyzer.h
│   │   │   ├── FidHasher.h
│   │   │   ├── FileArchiveBasedDataTypeManager.h
│   │   │   ├── FileBasedDataTypeManager.h
│   │   │   ├── FileDataTypeManager.h
│   │   │   ├── FileInUseException.h
│   │   │   ├── FileSystemFactoryDependencyException.h
│   │   │   ├── FileTimeDataType.h
│   │   │   ├── FindNoReturnFunctionsAnalyzer.h
│   │   │   ├── Fixup.h
│   │   │   ├── fks_generated.h
│   │   │   ├── FksLibrary.h
│   │   │   ├── Float10DataType.h
│   │   │   ├── Float16DataType.h
│   │   │   ├── Float2DataType.h
│   │   │   ├── Float4DataType.h
│   │   │   ├── Float8DataType.h
│   │   │   ├── FloatComplexDataType.h
│   │   │   ├── FloatDataType.h
│   │   │   ├── FloatFormat.h
│   │   │   ├── FloatingPointPrecisionSettingsDefinition.h
│   │   │   ├── FlowInfo.h
│   │   │   ├── FlowOverride.h
│   │   │   ├── FNV1a64.h
│   │   │   ├── FolderNotEmptyException.h
│   │   │   ├── FormatSettingsDefinition.h
│   │   │   ├── FormatStringAnalyzer.h
│   │   │   ├── FragmentDB.h
│   │   │   ├── FragmentMergeAnalyzer.h
│   │   │   ├── FuncCallSpecs.h
│   │   │   ├── Funcdata.h
│   │   │   ├── Function.h
│   │   │   ├── FunctionAnalyzer.h
│   │   │   ├── FunctionBodyFinalizer.h
│   │   │   ├── FunctionComparisonException.h
│   │   │   ├── FunctionDefinition.h
│   │   │   ├── FunctionDefinitionDataType.h
│   │   │   ├── FunctionDiscoveryAnalyzer.h
│   │   │   ├── FunctionDiscoveryAnalyzerAdapter.h
│   │   │   ├── FunctionFingerprint.h
│   │   │   ├── FunctionIterator.h
│   │   │   ├── FunctionManager.h
│   │   │   ├── FunctionOverlapException.h
│   │   │   ├── FunctionSignature.h
│   │   │   ├── FunctionSignatureImpl.h
│   │   │   ├── FunctionStartAnalyzer.h
│   │   │   ├── FunctionStartDataPostAnalyzer.h
│   │   │   ├── FunctionStartFuncAnalyzer.h
│   │   │   ├── FunctionStartPostAnalyzer.h
│   │   │   ├── FunctionStartPreFuncAnalyzer.h
│   │   │   ├── FunctionTag.h
│   │   │   ├── FunctionTagChangeSet.h
│   │   │   ├── FunctionTagImpl.h
│   │   │   ├── FunctionTagManager.h
│   │   │   ├── FunctionTagManagerImpl.h
│   │   │   ├── GccExceptionAnalyzer.h
│   │   │   ├── GenericCallingConvention.h
│   │   │   ├── GenericDataType.h
│   │   │   ├── GhidraBundleException.h
│   │   │   ├── GhidraClass.h
│   │   │   ├── GhidraDataConverter.h
│   │   │   ├── GhidraException.h
│   │   │   ├── GhidraLanguagePropertyKeys.h
│   │   │   ├── GhidraScriptLoadException.h
│   │   │   ├── GifDataType.h
│   │   │   ├── GIFResource.h
│   │   │   ├── GlobalContext.h
│   │   │   ├── GlobalSymbolMap.h
│   │   │   ├── GnuDemanglerAnalyzer.h
│   │   │   ├── GoBuildInfoParser.h
│   │   │   ├── GolangStringAnalyzer.h
│   │   │   ├── GolangSymbolAnalyzer.h
│   │   │   ├── GoRttiParser.h
│   │   │   ├── GotoStack.h
│   │   │   ├── GraphException.h
│   │   │   ├── Group.h
│   │   │   ├── GuardCfgAnalyzer.h
│   │   │   ├── HCS12ConventionAnalyzer.h
│   │   │   ├── Heritage.h
│   │   │   ├── HexagonAnalyzer.h
│   │   │   ├── HexagonPrologEpilogAnalyzer.h
│   │   │   ├── HexagonThunkAnalyzer.h
│   │   │   ├── HexagonUnsupportSemanticAnalyzer.h
│   │   │   ├── HiddenReturnAssign.h
│   │   │   ├── HighFunction.h
│   │   │   ├── HighSymbol.h
│   │   │   ├── HighVariable.h
│   │   │   ├── HomogeneousAggregate.h
│   │   │   ├── IBO32DataType.h
│   │   │   ├── IBO64DataType.h
│   │   │   ├── iBootImAnalyzer.h
│   │   │   ├── ICategory.h
│   │   │   ├── IconMaskResourceDataType.h
│   │   │   ├── IconResource.h
│   │   │   ├── IconResourceDataType.h
│   │   │   ├── IdentityNameTransformer.h
│   │   │   ├── IllegalCharCppTransformer.h
│   │   │   ├── IllegalFieldAccessException.h
│   │   │   ├── IllegalRenameException.h
│   │   │   ├── Img2Analyzer.h
│   │   │   ├── Img3Analyzer.h
│   │   │   ├── ImmutableAddressSet.h
│   │   │   ├── ImportThunkAnalyzer.h
│   │   │   ├── ImproperUseException.h
│   │   │   ├── IncompatibleLanguageException.h
│   │   │   ├── IncompatibleMaskException.h
│   │   │   ├── IndexedDynamicDataType.h
│   │   │   ├── InjectContext.h
│   │   │   ├── InjectionErrorPcodeExecutionException.h
│   │   │   ├── InjectPayload.h
│   │   │   ├── InjectPayloadSleigh.h
│   │   │   ├── InjectPayloadSubtypes.h
│   │   │   ├── InputListType.h
│   │   │   ├── Instruction.h
│   │   │   ├── InstructionBlock.h
│   │   │   ├── InstructionBlockFlow.h
│   │   │   ├── InstructionContext.h
│   │   │   ├── InstructionDecodeException.h
│   │   │   ├── InstructionError.h
│   │   │   ├── InstructionIterator.h
│   │   │   ├── InstructionPcodeOverride.h
│   │   │   ├── InstructionPrototype.h
│   │   │   ├── InstructionSet.h
│   │   │   ├── InstructionStub.h
│   │   │   ├── InsufficientBytesException.h
│   │   │   ├── Integer16DataType.h
│   │   │   ├── Integer3DataType.h
│   │   │   ├── Integer5DataType.h
│   │   │   ├── Integer6DataType.h
│   │   │   ├── Integer7DataType.h
│   │   │   ├── IntegerDataType.h
│   │   │   ├── IntegerSignednessFormattingModeSettingsDefinition.h
│   │   │   ├── InternalDataTypeComponent.h
│   │   │   ├── InterruptPcodeExecutionException.h
│   │   │   ├── IntersectionAddressSetView.h
│   │   │   ├── IntPropertyMap.h
│   │   │   ├── IntRangeMap.h
│   │   │   ├── InvalidAddressException.h
│   │   │   ├── InvalidatedListener.h
│   │   │   ├── InvalidDataException.h
│   │   │   ├── InvalidDataTypeException.h
│   │   │   ├── InvalidInputException.h
│   │   │   ├── InvalidNameException.h
│   │   │   ├── InvalidNTHeaderException.h
│   │   │   ├── InvalidPrototype.h
│   │   │   ├── InvalidWindowsHeaderException.h
│   │   │   ├── IOCancelledException.h
│   │   │   ├── iOS_Analyzer.h
│   │   │   ├── iOS_FixupArmSymbolsAnalyzer.h
│   │   │   ├── iOS_KextStubFixupAnalyzer.h
│   │   │   ├── JavaAnalyzer.h
│   │   │   ├── JavaEnumSettingsDefinition.h
│   │   │   ├── JPEGDataType.h
│   │   │   ├── JumpTable.h
│   │   │   ├── JvmSwitchAnalyzer.h
│   │   │   ├── KeyRange.h
│   │   │   ├── KnownFunctionHashes.h
│   │   │   ├── LabelHistory.h
│   │   │   ├── LabelString.h
│   │   │   ├── Language.h
│   │   │   ├── LanguageCompilerSpecPair.h
│   │   │   ├── LanguageCompilerSpecQuery.h
│   │   │   ├── LanguageDescription.h
│   │   │   ├── LanguageID.h
│   │   │   ├── LanguageNotFoundException.h
│   │   │   ├── LanguageProvider.h
│   │   │   ├── LanguageService.h
│   │   │   ├── LanguageVersionException.h
│   │   │   ├── LEB128.h
│   │   │   ├── Library.h
│   │   │   ├── LinkedByteBuffer.h
│   │   │   ├── Listing.h
│   │   │   ├── ListingAddressCorrelation.h
│   │   │   ├── ListLinked.h
│   │   │   ├── LoaderOpinionException.h
│   │   │   ├── LoadException.h
│   │   │   ├── LoadImage.h
│   │   │   ├── LocalSymbolMap.h
│   │   │   ├── LocalVariable.h
│   │   │   ├── LocalVariableImpl.h
│   │   │   ├── Location.h
│   │   │   ├── LockException.h
│   │   │   ├── LongDataType.h
│   │   │   ├── LongDoubleComplexDataType.h
│   │   │   ├── LongDoubleDataType.h
│   │   │   ├── LongIterator.h
│   │   │   ├── LongLongDataType.h
│   │   │   ├── LongPropertyMap.h
│   │   │   ├── LoongsonAnalyzer.h
│   │   │   ├── LowlevelError.h
│   │   │   ├── LSHException.h
│   │   │   ├── LzssAnalyzer.h
│   │   │   ├── MacException.h
│   │   │   ├── MachException.h
│   │   │   ├── MachoAnalyzer.h
│   │   │   ├── MachoConstructorDestructorAnalyzer.h
│   │   │   ├── MachoFunctionStartsAnalyzer.h
│   │   │   ├── MacintoshTimeStampDataType.h
│   │   │   ├── MainRecognitionAnalyzer.h
│   │   │   ├── ManagerDB.h
│   │   │   ├── ManualEntry.h
│   │   │   ├── MappedDataEntry.h
│   │   │   ├── MappedEntry.h
│   │   │   ├── Mask.h
│   │   │   ├── MaskImpl.h
│   │   │   ├── MathUtilities.h
│   │   │   ├── MDException.h
│   │   │   ├── MemBuffer.h
│   │   │   ├── MemBufferImageInputStream.h
│   │   │   ├── MemBufferInputStream.h
│   │   │   ├── MemBufferMixin.h
│   │   │   ├── Memory.h
│   │   │   ├── MemoryAccessException.h
│   │   │   ├── MemoryBlock.h
│   │   │   ├── MemoryBlockDefinition.h
│   │   │   ├── MemoryBlockException.h
│   │   │   ├── MemoryBlockListener.h
│   │   │   ├── MemoryBlockSourceInfo.h
│   │   │   ├── MemoryBlockStub.h
│   │   │   ├── MemoryBlockType.h
│   │   │   ├── MemoryBufferImpl.h
│   │   │   ├── MemoryByteIterator.h
│   │   │   ├── MemoryByteProvider.h
│   │   │   ├── MemoryConflictException.h
│   │   │   ├── MemoryConstants.h
│   │   │   ├── MemReferenceImpl.h
│   │   │   ├── MenuResourceDataType.h
│   │   │   ├── MessageLog.h
│   │   │   ├── MetaDataType.h
│   │   │   ├── Metatype.h
│   │   │   ├── MetaTypeFilter.h
│   │   │   ├── MicrosoftDemanglerAnalyzer.h
│   │   │   ├── MIDIDataType.h
│   │   │   ├── MingwRelocationAnalyzer.h
│   │   │   ├── MipsAddressAnalyzer.h
│   │   │   ├── MipsPreAnalyzer.h
│   │   │   ├── MipsSymbolAnalyzer.h
│   │   │   ├── MissingBuiltInDataType.h
│   │   │   ├── ModelRule.h
│   │   │   ├── ModuleDB.h
│   │   │   ├── ModuleManager.h
│   │   │   ├── Motorola68KAnalyzer.h
│   │   │   ├── Msg.h
│   │   │   ├── MsvcDemangler.h
│   │   │   ├── MultiMemberAssign.h
│   │   │   ├── MultipleProgramsException.h
│   │   │   ├── MultiSlotAssign.h
│   │   │   ├── MultiSlotDualAssign.h
│   │   │   ├── MutabilitySettingsDefinition.h
│   │   │   ├── MutableMemBuffer.h
│   │   │   ├── Namespace.h
│   │   │   ├── NamespaceManager.h
│   │   │   ├── NameTransformer.h
│   │   │   ├── NamingService.h
│   │   │   ├── NDS32Analyzer.h
│   │   │   ├── NeedsBackfillException.h
│   │   │   ├── NestedDelaySlotException.h
│   │   │   ├── NewExt4Analyzer.h
│   │   │   ├── NoDatabaseException.h
│   │   │   ├── NoDefaultCodecException.h
│   │   │   ├── NoisyStructureBuilder.h
│   │   │   ├── NoPreLinkSectionException.h
│   │   │   ├── NoReturnFunctionAnalyzer.h
│   │   │   ├── NormalizedAddressSet.h
│   │   │   ├── NoSettings.h
│   │   │   ├── NoSuchIndexException.h
│   │   │   ├── NotConnectedException.h
│   │   │   ├── NotEmptyException.h
│   │   │   ├── NotFoundException.h
│   │   │   ├── NotOwnerException.h
│   │   │   ├── NoTransactionException.h
│   │   │   ├── NotYetImplementedException.h
│   │   │   ├── NoValueException.h
│   │   │   ├── NumberSettingsDefinition.h
│   │   │   ├── NumericUtilities.h
│   │   │   ├── OatExecAnalyzer.h
│   │   │   ├── OatHeaderAnalyzer.h
│   │   │   ├── ObjcMessageAnalyzer.h
│   │   │   ├── ObjcTypeMetadataAnalyzer.h
│   │   │   ├── ObjectPropertyMap.h
│   │   │   ├── ObjectStorage.h
│   │   │   ├── ObsoleteException.h
│   │   │   ├── OdexHeaderFormatAnalyzer.h
│   │   │   ├── OffsetMaskSettingsDefinition.h
│   │   │   ├── OffsetReference.h
│   │   │   ├── OffsetShiftSettingsDefinition.h
│   │   │   ├── OldLanguageMappingService.h
│   │   │   ├── OmfException.h
│   │   │   ├── OpBehavior.h
│   │   │   ├── OpCode.h
│   │   │   ├── OperandReferenceAnalyzer.h
│   │   │   ├── OperandRepresentationList.h
│   │   │   ├── OperandType.h
│   │   │   ├── OpinionException.h
│   │   │   ├── OptionException.h
│   │   │   ├── Options.h
│   │   │   ├── OptionsVetoException.h
│   │   │   ├── OrQuery.h
│   │   │   ├── OSGiException.h
│   │   │   ├── OverlappingFunctionException.h
│   │   │   ├── OverlappingNamespaceException.h
│   │   │   ├── OverlayAddressSpace.h
│   │   │   ├── PackedBytes.h
│   │   │   ├── PackedDecode.h
│   │   │   ├── PackedDecodeOverlay.h
│   │   │   ├── PackedEncode.h
│   │   │   ├── PackedEncodeOverlay.h
│   │   │   ├── PackingType.h
│   │   │   ├── PaddingSettingsDefinition.h
│   │   │   ├── ParallelInstructionLanguageHelper.h
│   │   │   ├── ParamEntry.h
│   │   │   ├── Parameter.h
│   │   │   ├── ParameterConflictException.h
│   │   │   ├── ParameterDefinition.h
│   │   │   ├── ParameterDefinitionImpl.h
│   │   │   ├── ParameterImpl.h
│   │   │   ├── ParameterPieces.h
│   │   │   ├── ParamList.h
│   │   │   ├── ParamListImpl.h
│   │   │   ├── ParamListRegisterOut.h
│   │   │   ├── ParamListStandard.h
│   │   │   ├── ParamListStandardOut.h
│   │   │   ├── ParseException.h
│   │   │   ├── ParserContext.h
│   │   │   ├── ParserWalker.h
│   │   │   ├── PartialUnion.h
│   │   │   ├── PascalString255DataType.h
│   │   │   ├── PascalStringDataType.h
│   │   │   ├── PascalUnicodeDataType.h
│   │   │   ├── PatchEncoder.h
│   │   │   ├── PatchPackedEncode.h
│   │   │   ├── PcodeBlockBasic.h
│   │   │   ├── PcodeCapstoneMapper.h
│   │   │   ├── PcodeDataTypeManager.h
│   │   │   ├── PcodeException.h
│   │   │   ├── PcodeExecutionException.h
│   │   │   ├── PcodeFactory.h
│   │   │   ├── PcodeFrame.h
│   │   │   ├── PcodeInject.h
│   │   │   ├── PcodeInjectLibrary.h
│   │   │   ├── PcodeOp.h
│   │   │   ├── PcodeOpAST.h
│   │   │   ├── PcodeOpBank.h
│   │   │   ├── PcodeOverride.h
│   │   │   ├── PcodeParser.h
│   │   │   ├── PcodeSyntaxTree.h
│   │   │   ├── PdbAnalyzer.h
│   │   │   ├── PdbException.h
│   │   │   ├── PdbParser.h
│   │   │   ├── PdbUniversalAnalyzer.h
│   │   │   ├── PEExceptionAnalyzer.h
│   │   │   ├── PefAnalyzer.h
│   │   │   ├── PefDebugAnalyzer.h
│   │   │   ├── PefException.h
│   │   │   ├── Pic12Analyzer.h
│   │   │   ├── Pic16Analyzer.h
│   │   │   ├── Pic17c7xxAnalyzer.h
│   │   │   ├── Pic18Analyzer.h
│   │   │   ├── Pic24DInitAnalyzer.h
│   │   │   ├── PicSwitchAnalyzer.h
│   │   │   ├── Playable.h
│   │   │   ├── PluggableServiceRegistryException.h
│   │   │   ├── PluginConstructionException.h
│   │   │   ├── PluginException.h
│   │   │   ├── PngDataType.h
│   │   │   ├── PNGFormatException.h
│   │   │   ├── PngResource.h
│   │   │   ├── Pointer.h
│   │   │   ├── Pointer16DataType.h
│   │   │   ├── Pointer24DataType.h
│   │   │   ├── Pointer32DataType.h
│   │   │   ├── Pointer40DataType.h
│   │   │   ├── Pointer48DataType.h
│   │   │   ├── Pointer56DataType.h
│   │   │   ├── Pointer64DataType.h
│   │   │   ├── Pointer8DataType.h
│   │   │   ├── PointerDataType.h
│   │   │   ├── PointerType.h
│   │   │   ├── PointerTypedef.h
│   │   │   ├── PointerTypedefBuilder.h
│   │   │   ├── PointerTypeSettingsDefinition.h
│   │   │   ├── PortableExecutableAnalyzer.h
│   │   │   ├── PositionMatchFilter.h
│   │   │   ├── PowerPCAddressAnalyzer.h
│   │   │   ├── PreprocessorException.h
│   │   │   ├── PrimitiveExtractor.h
│   │   │   ├── PrintC.h
│   │   │   ├── PrintJava.h
│   │   │   ├── PrintLanguage.h
│   │   │   ├── PrivateSaveable.h
│   │   │   ├── Processor.h
│   │   │   ├── ProcessorContext.h
│   │   │   ├── ProcessorContextImpl.h
│   │   │   ├── ProcessorContextView.h
│   │   │   ├── ProcessorNotFoundException.h
│   │   │   ├── ProcessorSymbolType.h
│   │   │   ├── Program.h
│   │   │   ├── ProgramAddressFactory.h
│   │   │   ├── ProgramArchitecture.h
│   │   │   ├── ProgramArchitectureTranslator.h
│   │   │   ├── ProgramBasedDataTypeManager.h
│   │   │   ├── ProgramChangeRecord.h
│   │   │   ├── ProgramChangeSet.h
│   │   │   ├── ProgramConflictException.h
│   │   │   ├── ProgramContext.h
│   │   │   ├── ProgramContextImpl.h
│   │   │   ├── ProgramDB.h
│   │   │   ├── ProgramFragment.h
│   │   │   ├── ProgramModule.h
│   │   │   ├── ProgramProcessorContext.h
│   │   │   ├── ProgramTreeChangeSet.h
│   │   │   ├── ProgramUserData.h
│   │   │   ├── ProjectArchiveBasedDataTypeManager.h
│   │   │   ├── PropagateExternalParametersAnalyzer.h
│   │   │   ├── PropertyMap.h
│   │   │   ├── PropertyMapManager.h
│   │   │   ├── PropertyMapManagerImpl.h
│   │   │   ├── PropertySet.h
│   │   │   ├── PropertyTypeMismatchException.h
│   │   │   ├── ProtectedAddressSpace.h
│   │   │   ├── PrototypeModel.h
│   │   │   ├── PrototypeModelError.h
│   │   │   ├── PrototypeModelMerged.h
│   │   │   ├── PrototypePieces.h
│   │   │   ├── QualifierFilter.h
│   │   │   ├── Query.h
│   │   │   ├── QueryDatabaseException.h
│   │   │   ├── QWordDataType.h
│   │   │   ├── ReadOnlyDataTypeComponent.h
│   │   │   ├── ReadOnlyException.h
│   │   │   ├── ReadOnlyProcessorContext.h
│   │   │   ├── Reference.h
│   │   │   ├── ReferenceIterator.h
│   │   │   ├── ReferenceIteratorAdapter.h
│   │   │   ├── ReferenceListener.h
│   │   │   ├── ReferenceManager.h
│   │   │   ├── ReferenceManagerImpl.h
│   │   │   ├── RefType.h
│   │   │   ├── RefTypeFactory.h
│   │   │   ├── Register.h
│   │   │   ├── RegisterBuilder.h
│   │   │   ├── RegisterChangeSet.h
│   │   │   ├── RegisterManager.h
│   │   │   ├── RegisterTranslator.h
│   │   │   ├── RegisterTree.h
│   │   │   ├── RegisterValue.h
│   │   │   ├── RegisterValueException.h
│   │   │   ├── Relocation.h
│   │   │   ├── RelocationException.h
│   │   │   ├── RelocationHandler.h
│   │   │   ├── RelocationResult.h
│   │   │   ├── RelocationTable.h
│   │   │   ├── RelocationTableImpl.h
│   │   │   ├── RelocationUtil.h
│   │   │   ├── RenderUnicodeSettingsDefinition.h
│   │   │   ├── RepeatableComment.h
│   │   │   ├── RepeatCountDataType.h
│   │   │   ├── RepeatedDynamicDataType.h
│   │   │   ├── RepeatedStringDataType.h
│   │   │   ├── RepositoryNotFoundException.h
│   │   │   ├── ReservedNameException.h
│   │   │   ├── Resource.h
│   │   │   ├── ReturnParameterImpl.h
│   │   │   ├── RGB16ColorDataType.h
│   │   │   ├── RGB16EncodingSettingsDefinition.h
│   │   │   ├── RGB32ColorDataType.h
│   │   │   ├── RGB32EncodingSettingsDefinition.h
│   │   │   ├── RISCVAddressAnalyzer.h
│   │   │   ├── RollbackException.h
│   │   │   ├── RttiAnalyzer.h
│   │   │   ├── Rule.h
│   │   │   ├── RuntimeIOException.h
│   │   │   ├── RustDemanglerAnalyzer.h
│   │   │   ├── RustStringAnalyzer.h
│   │   │   ├── Saveable.h
│   │   │   ├── Scalar.h
│   │   │   ├── ScalarOperandAnalyzer.h
│   │   │   ├── ScalarOverflowException.h
│   │   │   ├── Scope.h
│   │   │   ├── ScorePlayer.h
│   │   │   ├── SegmentedAddress.h
│   │   │   ├── SegmentedAddressSpace.h
│   │   │   ├── SegmentedCallingConventionAnalyzer.h
│   │   │   ├── SegmentedCodePointerDataType.h
│   │   │   ├── SegmentMismatchException.h
│   │   │   ├── SequenceNumber.h
│   │   │   ├── ServiceConstructionException.h
│   │   │   ├── Settings.h
│   │   │   ├── SettingsDefinition.h
│   │   │   ├── SettingsImpl.h
│   │   │   ├── SettingsPropertyMap.h
│   │   │   ├── SH4AddressAnalyzer.h
│   │   │   ├── SH4EarlyAddressAnalyzer.h
│   │   │   ├── SharedReturnAnalyzer.h
│   │   │   ├── SharedReturnJumpAnalyzer.h
│   │   │   ├── ShiftedAddressDataType.h
│   │   │   ├── ShiftedReference.h
│   │   │   ├── ShortDataType.h
│   │   │   ├── SignatureSource.h
│   │   │   ├── SignedByteDataType.h
│   │   │   ├── SignedCharDataType.h
│   │   │   ├── SignedDWordDataType.h
│   │   │   ├── SignedLeb128DataType.h
│   │   │   ├── SignednessFormatMode.h
│   │   │   ├── SignedQWordDataType.h
│   │   │   ├── SignedWordDataType.h
│   │   │   ├── SimpleCRC32.h
│   │   │   ├── SingleAddressSetCollection.h
│   │   │   ├── SizeRestrictedFilter.h
│   │   │   ├── SledException.h
│   │   │   ├── Sleigh.h
│   │   │   ├── SleighCompilerSpecDescription.h
│   │   │   ├── SleighDebugLogger.h
│   │   │   ├── SleighException.h
│   │   │   ├── SleighFileException.h
│   │   │   ├── SleighFileLockException.h
│   │   │   ├── SleighInstructionPrototype.h
│   │   │   ├── SleighLanguage.h
│   │   │   ├── SleighLanguageDescription.h
│   │   │   ├── SleighLanguageFile.h
│   │   │   ├── SleighLanguageProvider.h
│   │   │   ├── SleighLinkException.h
│   │   │   ├── SleighParserContext.h
│   │   │   ├── SolverException.h
│   │   │   ├── SorterException.h
│   │   │   ├── SourceArchive.h
│   │   │   ├── SourceArchiveImpl.h
│   │   │   ├── SourceFile.h
│   │   │   ├── SourceFileIdType.h
│   │   │   ├── SourceFileManager.h
│   │   │   ├── SourceFileManagerImpl.h
│   │   │   ├── SourceMapEntry.h
│   │   │   ├── SourceMapEntryIterator.h
│   │   │   ├── SourcePathTransformer.h
│   │   │   ├── SourcePathTransformRecord.h
│   │   │   ├── SourceType.h
│   │   │   ├── SpaceNames.h
│   │   │   ├── SparcAnalyzer.h
│   │   │   ├── SparcEarlyAddressAnalyzer.h
│   │   │   ├── SpecialAddress.h
│   │   │   ├── SpecXmlUtils.h
│   │   │   ├── StackFrame.h
│   │   │   ├── StackFrameImpl.h
│   │   │   ├── StackReference.h
│   │   │   ├── StackReferenceAnalyzer.h
│   │   │   ├── StackReferenceImpl.h
│   │   │   ├── StackVariableAnalyzer.h
│   │   │   ├── StackVariableComparator.h
│   │   │   ├── StandAloneDataTypeManager.h
│   │   │   ├── StartedGhidraProcessExitedException.h
│   │   │   ├── StatusListener.h
│   │   │   ├── StopWaitingException.h
│   │   │   ├── StorageClass.h
│   │   │   ├── StringDataInstance.h
│   │   │   ├── StringDataType.h
│   │   │   ├── StringIngest.h
│   │   │   ├── StringLayoutEnum.h
│   │   │   ├── StringPropertyMap.h
│   │   │   ├── StringRenderBuilder.h
│   │   │   ├── StringRenderParser.h
│   │   │   ├── StringsAnalyzer.h
│   │   │   ├── StringSettingsDefinition.h
│   │   │   ├── StringUTF8DataType.h
│   │   │   ├── StringUtilities.h
│   │   │   ├── Structure.h
│   │   │   ├── StructureDataType.h
│   │   │   ├── StructuredBlock.h
│   │   │   ├── StructuredDynamicDataType.h
│   │   │   ├── StructureFactory.h
│   │   │   ├── StructureInternal.h
│   │   │   ├── StubListing.h
│   │   │   ├── StubMemory.h
│   │   │   ├── SuspendedPcodeExecutionException.h
│   │   │   ├── SwiftDemanglerAnalyzer.h
│   │   │   ├── SwiftTypeMetadataAnalyzer.h
│   │   │   ├── Symbol.h
│   │   │   ├── SymbolChangeSet.h
│   │   │   ├── SymbolEntry.h
│   │   │   ├── SymbolicPropogator.h
│   │   │   ├── SymbolIterator.h
│   │   │   ├── SymbolIteratorAdapter.h
│   │   │   ├── SymbolManager.h
│   │   │   ├── SymbolPath.h
│   │   │   ├── SymbolTable.h
│   │   │   ├── SymbolTableListener.h
│   │   │   ├── SymbolType.h
│   │   │   ├── SymbolUtilities.h
│   │   │   ├── SymmetricDifferenceAddressSetView.h
│   │   │   ├── TaskMonitor.h
│   │   │   ├── TEBAnalyzer.h
│   │   │   ├── TerminatedSettingsDefinition.h
│   │   │   ├── TerminatedStringDataType.h
│   │   │   ├── TerminatedTransactionException.h
│   │   │   ├── TerminatedUnicode32DataType.h
│   │   │   ├── TerminatedUnicodeDataType.h
│   │   │   ├── ThunkFunction.h
│   │   │   ├── ThunkReference.h
│   │   │   ├── ToyAnalyzer.h
│   │   │   ├── TraceClosedException.h
│   │   │   ├── TraceConflictedMappingException.h
│   │   │   ├── TraceOverlappedRegionException.h
│   │   │   ├── TrackedRegisterSeeder.h
│   │   │   ├── Translate.h
│   │   │   ├── TranslationSettingsDefinition.h
│   │   │   ├── TreeManager.h
│   │   │   ├── TriConsumer.h
│   │   │   ├── TwoWayBreakdownAddressRangeIterator.h
│   │   │   ├── TypeDatabase.h
│   │   │   ├── TypeDef.h
│   │   │   ├── TypedefDataType.h
│   │   │   ├── TypeDefSettingsDefinition.h
│   │   │   ├── TypeFactory.h
│   │   │   ├── TypeMismatchException.h
│   │   │   ├── TypePropagation.h
│   │   │   ├── Types.h
│   │   │   ├── UbiException.h
│   │   │   ├── ULEB128.h
│   │   │   ├── UnableToGetLockException.h
│   │   │   ├── Undefined.h
│   │   │   ├── Undefined1DataType.h
│   │   │   ├── Undefined2DataType.h
│   │   │   ├── Undefined3DataType.h
│   │   │   ├── Undefined4DataType.h
│   │   │   ├── Undefined5DataType.h
│   │   │   ├── Undefined6DataType.h
│   │   │   ├── Undefined7DataType.h
│   │   │   ├── Undefined8DataType.h
│   │   │   ├── UndefinedValueException.h
│   │   │   ├── Unicode32DataType.h
│   │   │   ├── UnicodeDataType.h
│   │   │   ├── UnimplementedCallOtherException.h
│   │   │   ├── UnimplementedInstructionException.h
│   │   │   ├── Union.h
│   │   │   ├── UnionAddressRangeIterator.h
│   │   │   ├── UnionAddressSetView.h
│   │   │   ├── UnionDataType.h
│   │   │   ├── UnionFacetSymbol.h
│   │   │   ├── UnionInternal.h
│   │   │   ├── UniqueLayout.h
│   │   │   ├── UniversalID.h
│   │   │   ├── UnknownArtStorageModeException.h
│   │   │   ├── UnknownContextException.h
│   │   │   ├── UnknownDataException.h
│   │   │   ├── UnknownInstructionException.h
│   │   │   ├── UnknownRegister.h
│   │   │   ├── UnknownStatePcodeExecutionException.h
│   │   │   ├── UnsatisfiedFieldsException.h
│   │   │   ├── UnsatisfiedParameterException.h
│   │   │   ├── UnsignedCharDataType.h
│   │   │   ├── UnsignedInteger16DataType.h
│   │   │   ├── UnsignedInteger3DataType.h
│   │   │   ├── UnsignedInteger5DataType.h
│   │   │   ├── UnsignedInteger6DataType.h
│   │   │   ├── UnsignedInteger7DataType.h
│   │   │   ├── UnsignedIntegerDataType.h
│   │   │   ├── UnsignedLeb128DataType.h
│   │   │   ├── UnsignedLongDataType.h
│   │   │   ├── UnsignedLongLongDataType.h
│   │   │   ├── UnsignedShortDataType.h
│   │   │   ├── UnsupportedArtVersionException.h
│   │   │   ├── UnsupportedFloatFormatException.h
│   │   │   ├── UnsupportedOatVersionException.h
│   │   │   ├── UnsupportedVdexVersionException.h
│   │   │   ├── UserAccessException.h
│   │   │   ├── UseropSymbol.h
│   │   │   ├── UsrException.h
│   │   │   ├── ValuesMapParseException.h
│   │   │   ├── VarargsFilter.h
│   │   │   ├── Variable.h
│   │   │   ├── VariableFilter.h
│   │   │   ├── VariableImpl.h
│   │   │   ├── VariableOffset.h
│   │   │   ├── VariableSizeException.h
│   │   │   ├── VariableStorage.h
│   │   │   ├── VariableUtilities.h
│   │   │   ├── Varnode.h
│   │   │   ├── VarnodeAST.h
│   │   │   ├── VarnodeBank.h
│   │   │   ├── VarnodeContext.h
│   │   │   ├── VarnodeTranslator.h
│   │   │   ├── VdexHeaderAnalyzer.h
│   │   │   ├── VersionedLanguageService.h
│   │   │   ├── VersionException.h
│   │   │   ├── VersionTrackingApplyException.h
│   │   │   ├── Vertex.h
│   │   │   ├── VoidDataType.h
│   │   │   ├── VoidPropertyMap.h
│   │   │   ├── VTAssociationStatusException.h
│   │   │   ├── WAVEDataType.h
│   │   │   ├── WideChar16DataType.h
│   │   │   ├── WideChar32DataType.h
│   │   │   ├── WideCharDataType.h
│   │   │   ├── WindowsResourceReferenceAnalyzer.h
│   │   │   ├── WordDataType.h
│   │   │   ├── WrappedMemBuffer.h
│   │   │   ├── X86Analyzer.h
│   │   │   ├── X86FunctionPurgeAnalyzer.h
│   │   │   ├── XmlAttributeException.h
│   │   │   ├── XmlDecode.h
│   │   │   ├── XmlEncode.h
│   │   │   ├── XmlParseException.h
│   │   │   └── XmlPullParser.h
│   │   └── gui
│   │       └── CutterSeekable.h
│   ├── lang
│   │   ├── BasicCompilerSpec.cpp
│   │   ├── GhidraLanguagePropertyKeys.cpp
│   │   ├── InjectContext.cpp
│   │   ├── InjectPayloadSubtypes.cpp
│   │   ├── InstructionError.cpp
│   │   ├── InvalidPrototype.cpp
│   │   ├── MaskImpl.cpp
│   │   ├── OldLanguageMappingService.cpp
│   │   └── PrototypeModelMerged.cpp
│   ├── listing
│   │   ├── CodeUnit.cpp
│   │   ├── CommentHistory.cpp
│   │   ├── Data.cpp
│   │   ├── DataIterator.cpp
│   │   ├── DataStub.cpp
│   │   ├── Instruction.cpp
│   │   ├── InstructionStub.cpp
│   │   ├── Library.cpp
│   │   ├── Listing.cpp
│   │   ├── StackVariableComparator.cpp
│   │   ├── StubListing.cpp
│   │   └── VariableFilter.cpp
│   ├── marshal
│   │   ├── XmlDecode.cpp
│   │   └── XmlEncode.cpp
│   ├── mem
│   │   ├── MemoryBlockStub.cpp
│   │   └── StubMemory.cpp
│   ├── memory
│   │   ├── ByteMemBufferImpl.cpp
│   │   ├── DataConverter.cpp
│   │   ├── DumbMemBufferImpl.cpp
│   │   ├── GhidraDataConverter.cpp
│   │   ├── MemBufferInputStream.cpp
│   │   ├── MemoryBufferImpl.cpp
│   │   └── WrappedMemBuffer.cpp
│   ├── pcode
│   │   ├── pcode
│   │   │   ├── EquateSymbol.cpp
│   │   │   ├── FunctionPrototype.cpp
│   │   │   ├── HighCodeSymbol.cpp
│   │   │   ├── HighConstant.cpp
│   │   │   ├── HighExternalSymbol.cpp
│   │   │   ├── HighFunction.cpp
│   │   │   ├── HighFunctionDBUtil.cpp
│   │   │   ├── HighFunctionShellSymbol.cpp
│   │   │   ├── HighFunctionSymbol.cpp
│   │   │   ├── HighGlobal.cpp
│   │   │   ├── HighLabelSymbol.cpp
│   │   │   ├── HighLocal.cpp
│   │   │   ├── HighOther.cpp
│   │   │   ├── HighParam.cpp
│   │   │   ├── HighParamID.cpp
│   │   │   ├── HighVariable.cpp
│   │   │   ├── JumpTable.cpp
│   │   │   └── ParamMeasure.cpp
│   │   ├── Action.cpp
│   │   ├── ActionManager.cpp
│   │   ├── AddrSpace.cpp
│   │   ├── AndFilter.cpp
│   │   ├── Architecture.cpp
│   │   ├── AssignAction.cpp
│   │   ├── AttributeId.cpp
│   │   ├── BlockGraph.cpp
│   │   ├── ByteIngest.cpp
│   │   ├── CachedEncoder.cpp
│   │   ├── CodeBlockImpl.cpp
│   │   ├── CodeBlockReferenceImpl.cpp
│   │   ├── Comment.cpp
│   │   ├── ConstructState.cpp
│   │   ├── ConsumeAs.cpp
│   │   ├── ConsumeExtra.cpp
│   │   ├── ConsumeRemaining.cpp
│   │   ├── ContextDatabase.cpp
│   │   ├── ContextSetting.cpp
│   │   ├── ConvertToPointer.cpp
│   │   ├── Cover.cpp
│   │   ├── Database.cpp
│   │   ├── DatatypeFilter.cpp
│   │   ├── DatatypeMatchFilter.cpp
│   │   ├── DynamicEntry.cpp
│   │   ├── DynamicHash.cpp
│   │   ├── ElementId.cpp
│   │   ├── Emulate.cpp
│   │   ├── EnigmaPipeline.cpp
│   │   ├── ExtCodeBlockImpl.cpp
│   │   ├── ExtraStack.cpp
│   │   ├── FloatFormat.cpp
│   │   ├── FlowInfo.cpp
│   │   ├── FlowOverride.cpp
│   │   ├── FuncCallSpecs.cpp
│   │   ├── Funcdata.cpp
│   │   ├── GlobalContext.cpp
│   │   ├── GlobalSymbolMap.cpp
│   │   ├── GotoStack.cpp
│   │   ├── Heritage.cpp
│   │   ├── HiddenReturnAssign.cpp
│   │   ├── HighFunction.cpp
│   │   ├── HighSymbol.cpp
│   │   ├── HighVariable.cpp
│   │   ├── HomogeneousAggregate.cpp
│   │   ├── InstructionPcodeOverride.cpp
│   │   ├── JumpTable.cpp
│   │   ├── LinkedByteBuffer.cpp
│   │   ├── LoadImage.cpp
│   │   ├── LocalSymbolMap.cpp
│   │   ├── MappedDataEntry.cpp
│   │   ├── MappedEntry.cpp
│   │   ├── MetaTypeFilter.cpp
│   │   ├── ModelRule.cpp
│   │   ├── MultiMemberAssign.cpp
│   │   ├── MultiSlotAssign.cpp
│   │   ├── MultiSlotDualAssign.cpp
│   │   ├── OpCode.cpp
│   │   ├── Options.cpp
│   │   ├── PackedBytes.cpp
│   │   ├── PackedDecode.cpp
│   │   ├── PackedDecodeOverlay.cpp
│   │   ├── PackedEncode.cpp
│   │   ├── PackedEncodeOverlay.cpp
│   │   ├── ParamListImpl.cpp
│   │   ├── ParamListRegisterOut.cpp
│   │   ├── ParamListStandard.cpp
│   │   ├── ParamListStandardOut.cpp
│   │   ├── PatchEncoder.cpp
│   │   ├── PatchPackedEncode.cpp
│   │   ├── PcodeBlockBasic.cpp
│   │   ├── PcodeCapstoneMapper.cpp
│   │   ├── PcodeInject.cpp
│   │   ├── PcodeInjectLibrary.cpp
│   │   ├── PcodeOp.cpp
│   │   ├── PcodeOpAST.cpp
│   │   ├── PcodeOpBank.cpp
│   │   ├── PcodeParser.cpp
│   │   ├── PcodeSyntaxTree.cpp
│   │   ├── PositionMatchFilter.cpp
│   │   ├── PrimitiveExtractor.cpp
│   │   ├── PrintC.cpp
│   │   ├── PrintJava.cpp
│   │   ├── PrintLanguage.cpp
│   │   ├── QualifierFilter.cpp
│   │   ├── RegisterManager.cpp
│   │   ├── RegisterTranslator.cpp
│   │   ├── RegisterTree.cpp
│   │   ├── Rule.cpp
│   │   ├── Scope.cpp
│   │   ├── SequenceNumber.cpp
│   │   ├── SizeRestrictedFilter.cpp
│   │   ├── Sleigh.cpp
│   │   ├── SleighLanguage.cpp
│   │   ├── SleighLanguageDescription.cpp
│   │   ├── SleighLanguageProvider.cpp
│   │   ├── StringIngest.cpp
│   │   ├── StructuredBlock.cpp
│   │   ├── SymbolEntry.cpp
│   │   ├── Translate.cpp
│   │   ├── TypeFactory.cpp
│   │   ├── TypePropagation.cpp
│   │   ├── UnionFacetSymbol.cpp
│   │   ├── UniqueLayout.cpp
│   │   ├── UseropSymbol.cpp
│   │   ├── VarargsFilter.cpp
│   │   ├── Varnode.cpp
│   │   ├── VarnodeAST.cpp
│   │   ├── VarnodeBank.cpp
│   │   └── VarnodeTranslator.cpp
│   ├── program
│   │   ├── AutoParameterImpl.cpp
│   │   ├── BookmarkManagerImpl.cpp
│   │   ├── CodeManager.cpp
│   │   ├── DatabaseAdapter.cpp
│   │   ├── DataTypeArchiveImpl.cpp
│   │   ├── DataTypeManagerImpl.cpp
│   │   ├── DisassemblerContextAdapter.cpp
│   │   ├── DynamicVariableStorage.cpp
│   │   ├── EquateTableImpl.cpp
│   │   ├── ExternalManagerImpl.cpp
│   │   ├── FragmentDB.cpp
│   │   ├── FunctionTagImpl.cpp
│   │   ├── FunctionTagManagerImpl.cpp
│   │   ├── InstructionBlock.cpp
│   │   ├── InstructionBlockFlow.cpp
│   │   ├── InstructionSet.cpp
│   │   ├── LocalVariableImpl.cpp
│   │   ├── ModuleDB.cpp
│   │   ├── ModuleManager.cpp
│   │   ├── NamespaceManager.cpp
│   │   ├── ParameterImpl.cpp
│   │   ├── ProcessorContextImpl.cpp
│   │   ├── ProgramAddressFactory.cpp
│   │   ├── ProgramChangeSet.cpp
│   │   ├── ProgramContextImpl.cpp
│   │   ├── ProgramDB.cpp
│   │   ├── ProgramProcessorContext.cpp
│   │   ├── PropertyMapManagerImpl.cpp
│   │   ├── ReadOnlyProcessorContext.cpp
│   │   ├── ReferenceManagerImpl.cpp
│   │   ├── RelocationTableImpl.cpp
│   │   ├── ReturnParameterImpl.cpp
│   │   ├── SourceFileManagerImpl.cpp
│   │   ├── SymbolManager.cpp
│   │   ├── TreeManager.cpp
│   │   ├── VariableImpl.cpp
│   │   ├── VariableStorage.cpp
│   │   └── VariableUtilities.cpp
│   ├── reloc
│   │   ├── RelocationResult.cpp
│   │   └── RelocationUtil.cpp
│   ├── settings
│   │   ├── AddressSpaceSettingsDefinition.cpp
│   │   ├── ComponentOffsetSettingsDefinition.cpp
│   │   ├── DataTypeMnemonicSettingsDefinition.cpp
│   │   ├── EndianSettingsDefinition.cpp
│   │   ├── FloatingPointPrecisionSettingsDefinition.cpp
│   │   ├── FormatSettingsDefinition.cpp
│   │   ├── IntegerSignednessFormattingModeSettingsDefinition.cpp
│   │   ├── MutabilitySettingsDefinition.cpp
│   │   ├── NumberSettingsDefinition.cpp
│   │   ├── OffsetMaskSettingsDefinition.cpp
│   │   ├── OffsetShiftSettingsDefinition.cpp
│   │   ├── PaddingSettingsDefinition.cpp
│   │   ├── PointerTypeSettingsDefinition.cpp
│   │   ├── RGB16EncodingSettingsDefinition.cpp
│   │   ├── RGB32EncodingSettingsDefinition.cpp
│   │   ├── SettingsDefinition.cpp
│   │   ├── SettingsImpl.cpp
│   │   └── TerminatedSettingsDefinition.cpp
│   ├── sleigh
│   │   ├── 6502
│   │   │   ├── 6502.cspec
│   │   │   ├── 6502.ldefs
│   │   │   ├── 6502.pspec
│   │   │   ├── 6502.sla
│   │   │   ├── 6502.slaspec
│   │   │   ├── 65c02.sla
│   │   │   └── 65c02.slaspec
│   │   ├── 68000
│   │   │   ├── 68000_register.cspec
│   │   │   ├── 68000.cspec
│   │   │   ├── 68000.ldefs
│   │   │   ├── 68000.pspec
│   │   │   ├── 68020.sla
│   │   │   ├── 68020.slaspec
│   │   │   ├── 68030.sla
│   │   │   ├── 68030.slaspec
│   │   │   ├── 68040.sla
│   │   │   ├── 68040.slaspec
│   │   │   ├── coldfire.sla
│   │   │   └── coldfire.slaspec
│   │   ├── 8048
│   │   │   ├── 8048.cspec
│   │   │   ├── 8048.ldefs
│   │   │   ├── 8048.pspec
│   │   │   ├── 8048.sla
│   │   │   └── 8048.slaspec
│   │   ├── 8051
│   │   │   ├── 80251.cspec
│   │   │   ├── 80251.pspec
│   │   │   ├── 80251.sla
│   │   │   ├── 80251.slaspec
│   │   │   ├── 80390.cspec
│   │   │   ├── 80390.sla
│   │   │   ├── 80390.slaspec
│   │   │   ├── 8051_archimedes.cspec
│   │   │   ├── 8051.cspec
│   │   │   ├── 8051.ldefs
│   │   │   ├── 8051.pspec
│   │   │   ├── 8051.sla
│   │   │   ├── 8051.slaspec
│   │   │   ├── cip-51.sla
│   │   │   ├── cip-51.slaspec
│   │   │   ├── keil-cx51.cspec
│   │   │   ├── mx51.cspec
│   │   │   ├── mx51.pspec
│   │   │   ├── mx51.sla
│   │   │   └── mx51.slaspec
│   │   ├── AARCH64
│   │   │   ├── AARCH64_apple.cspec
│   │   │   ├── AARCH64_AppleSilicon.sla
│   │   │   ├── AARCH64_AppleSilicon.slaspec
│   │   │   ├── AARCH64_golang.cspec
│   │   │   ├── AARCH64_ilp32.cspec
│   │   │   ├── AARCH64_swift.cspec
│   │   │   ├── AARCH64_win.cspec
│   │   │   ├── AARCH64.cspec
│   │   │   ├── AARCH64.ldefs
│   │   │   ├── AARCH64.pspec
│   │   │   ├── AARCH64.sla
│   │   │   ├── AARCH64.slaspec
│   │   │   ├── AARCH64BE.sla
│   │   │   ├── AARCH64BE.slaspec
│   │   │   └── AppleSilicon.ldefs
│   │   ├── ARM
│   │   │   ├── ARM_apcs.cspec
│   │   │   ├── ARM_v45.cspec
│   │   │   ├── ARM_v45.pspec
│   │   │   ├── ARM_win.cspec
│   │   │   ├── ARM.cspec
│   │   │   ├── ARM.ldefs
│   │   │   ├── ARM4_be.sla
│   │   │   ├── ARM4_be.slaspec
│   │   │   ├── ARM4_le.sla
│   │   │   ├── ARM4_le.slaspec
│   │   │   ├── ARM4t_be.sla
│   │   │   ├── ARM4t_be.slaspec
│   │   │   ├── ARM4t_le.sla
│   │   │   ├── ARM4t_le.slaspec
│   │   │   ├── ARM5_be.sla
│   │   │   ├── ARM5_be.slaspec
│   │   │   ├── ARM5_le.sla
│   │   │   ├── ARM5_le.slaspec
│   │   │   ├── ARM5t_be.sla
│   │   │   ├── ARM5t_be.slaspec
│   │   │   ├── ARM5t_le.sla
│   │   │   ├── ARM5t_le.slaspec
│   │   │   ├── ARM6_be.sla
│   │   │   ├── ARM6_be.slaspec
│   │   │   ├── ARM6_le.sla
│   │   │   ├── ARM6_le.slaspec
│   │   │   ├── ARM7_be.sla
│   │   │   ├── ARM7_be.slaspec
│   │   │   ├── ARM7_le.sla
│   │   │   ├── ARM7_le.slaspec
│   │   │   ├── ARM8_be.sla
│   │   │   ├── ARM8_be.slaspec
│   │   │   ├── ARM8_le.sla
│   │   │   ├── ARM8_le.slaspec
│   │   │   ├── ARM8m_be.sla
│   │   │   ├── ARM8m_be.slaspec
│   │   │   ├── ARM8m_le.sla
│   │   │   ├── ARM8m_le.slaspec
│   │   │   ├── ARMCortex.pspec
│   │   │   ├── ARMt_v45.pspec
│   │   │   ├── ARMt_v6.pspec
│   │   │   ├── ARMt.pspec
│   │   │   └── ARMtTHUMB.pspec
│   │   ├── BPF
│   │   │   ├── BPF_le.sla
│   │   │   ├── BPF_le.slaspec
│   │   │   ├── BPF.cspec
│   │   │   ├── BPF.ldefs
│   │   │   └── BPF.pspec
│   │   ├── Dalvik
│   │   │   ├── Dalvik_Base.cspec
│   │   │   ├── Dalvik_Base.pspec
│   │   │   ├── Dalvik_Base.sla
│   │   │   ├── Dalvik_Base.slaspec
│   │   │   ├── Dalvik_DEX_Android10.sla
│   │   │   ├── Dalvik_DEX_Android10.slaspec
│   │   │   ├── Dalvik_DEX_Android11.sla
│   │   │   ├── Dalvik_DEX_Android11.slaspec
│   │   │   ├── Dalvik_DEX_Android12.sla
│   │   │   ├── Dalvik_DEX_Android12.slaspec
│   │   │   ├── Dalvik_DEX_KitKat.sla
│   │   │   ├── Dalvik_DEX_KitKat.slaspec
│   │   │   ├── Dalvik_DEX_Lollipop.sla
│   │   │   ├── Dalvik_DEX_Lollipop.slaspec
│   │   │   ├── Dalvik_DEX_Marshmallow.sla
│   │   │   ├── Dalvik_DEX_Marshmallow.slaspec
│   │   │   ├── Dalvik_DEX_Nougat.sla
│   │   │   ├── Dalvik_DEX_Nougat.slaspec
│   │   │   ├── Dalvik_DEX_Oreo.sla
│   │   │   ├── Dalvik_DEX_Oreo.slaspec
│   │   │   ├── Dalvik_DEX_Pie.sla
│   │   │   ├── Dalvik_DEX_Pie.slaspec
│   │   │   ├── Dalvik_ODEX_KitKat.sla
│   │   │   ├── Dalvik_ODEX_KitKat.slaspec
│   │   │   └── Dalvik.ldefs
│   │   ├── eBPF
│   │   │   ├── eBPF_be.sla
│   │   │   ├── eBPF_be.slaspec
│   │   │   ├── eBPF_le.sla
│   │   │   ├── eBPF_le.slaspec
│   │   │   ├── eBPF.cspec
│   │   │   ├── eBPF.ldefs
│   │   │   └── eBPF.pspec
│   │   ├── Hexagon
│   │   │   ├── hexagon.cspec
│   │   │   ├── hexagon.ldefs
│   │   │   ├── hexagon.pspec
│   │   │   ├── hexagon.sla
│   │   │   └── hexagon.slaspec
│   │   ├── JVM
│   │   │   ├── JVM.cspec
│   │   │   ├── JVM.ldefs
│   │   │   ├── JVM.pspec
│   │   │   ├── JVM.sla
│   │   │   └── JVM.slaspec
│   │   ├── Loongarch
│   │   │   ├── ilp32d.cspec
│   │   │   ├── ilp32f.cspec
│   │   │   ├── loongarch.ldefs
│   │   │   ├── loongarch32_f32.sla
│   │   │   ├── loongarch32_f32.slaspec
│   │   │   ├── loongarch32_f64.sla
│   │   │   ├── loongarch32_f64.slaspec
│   │   │   ├── loongarch32.pspec
│   │   │   ├── loongarch64_f32.sla
│   │   │   ├── loongarch64_f32.slaspec
│   │   │   ├── loongarch64_f64.sla
│   │   │   ├── loongarch64_f64.slaspec
│   │   │   ├── loongarch64.pspec
│   │   │   ├── lp64d.cspec
│   │   │   └── lp64f.cspec
│   │   ├── MIPS
│   │   │   ├── mips.ldefs
│   │   │   ├── mips32_eabi.cspec
│   │   │   ├── mips32_fp64.cspec
│   │   │   ├── mips32.pspec
│   │   │   ├── mips32be.cspec
│   │   │   ├── mips32be.sla
│   │   │   ├── mips32be.slaspec
│   │   │   ├── mips32le.cspec
│   │   │   ├── mips32le.sla
│   │   │   ├── mips32le.slaspec
│   │   │   ├── mips32micro.pspec
│   │   │   ├── mips32R6.pspec
│   │   │   ├── mips32R6be.sla
│   │   │   ├── mips32R6be.slaspec
│   │   │   ├── mips32R6le.sla
│   │   │   ├── mips32R6le.slaspec
│   │   │   ├── mips64_32_n32.cspec
│   │   │   ├── mips64_32_o32.cspec
│   │   │   ├── mips64_32_o64.cspec
│   │   │   ├── mips64.pspec
│   │   │   ├── mips64be.cspec
│   │   │   ├── mips64be.sla
│   │   │   ├── mips64be.slaspec
│   │   │   ├── mips64le.cspec
│   │   │   ├── mips64le.sla
│   │   │   ├── mips64le.slaspec
│   │   │   ├── mips64micro.pspec
│   │   │   └── mips64R6.pspec
│   │   ├── NDS32
│   │   │   ├── nds32.cspec
│   │   │   ├── nds32.ldefs
│   │   │   ├── nds32.pspec
│   │   │   ├── nds32be.sla
│   │   │   ├── nds32be.slaspec
│   │   │   ├── nds32le.sla
│   │   │   └── nds32le.slaspec
│   │   ├── PA-RISC
│   │   │   ├── pa-risc.ldefs
│   │   │   ├── pa-risc32.cspec
│   │   │   ├── pa-risc32.pspec
│   │   │   ├── pa-risc32be.sla
│   │   │   └── pa-risc32be.slaspec
│   │   ├── PIC
│   │   │   ├── dsPIC30F.sla
│   │   │   ├── dsPIC30F.slaspec
│   │   │   ├── dsPIC33C.sla
│   │   │   ├── dsPIC33C.slaspec
│   │   │   ├── dsPIC33E.sla
│   │   │   ├── dsPIC33E.slaspec
│   │   │   ├── dsPIC33F.sla
│   │   │   ├── dsPIC33F.slaspec
│   │   │   ├── pic12c5xx.cspec
│   │   │   ├── pic12c5xx.ldefs
│   │   │   ├── pic12c5xx.pspec
│   │   │   ├── pic12c5xx.sla
│   │   │   ├── pic12c5xx.slaspec
│   │   │   ├── pic16.cspec
│   │   │   ├── pic16.ldefs
│   │   │   ├── pic16.pspec
│   │   │   ├── pic16.sla
│   │   │   ├── pic16.slaspec
│   │   │   ├── pic16c5x.cspec
│   │   │   ├── pic16c5x.ldefs
│   │   │   ├── pic16c5x.pspec
│   │   │   ├── pic16c5x.sla
│   │   │   ├── pic16c5x.slaspec
│   │   │   ├── pic16f.cspec
│   │   │   ├── pic16f.pspec
│   │   │   ├── pic16f.sla
│   │   │   ├── pic16f.slaspec
│   │   │   ├── pic17c7xx.cspec
│   │   │   ├── pic17c7xx.ldefs
│   │   │   ├── pic17c7xx.pspec
│   │   │   ├── pic17c7xx.sla
│   │   │   ├── pic17c7xx.slaspec
│   │   │   ├── pic18.cspec
│   │   │   ├── pic18.ldefs
│   │   │   ├── pic18.pspec
│   │   │   ├── pic18.sla
│   │   │   ├── pic18.slaspec
│   │   │   ├── PIC24.cspec
│   │   │   ├── PIC24.ldefs
│   │   │   ├── PIC24.pspec
│   │   │   ├── PIC24E.sla
│   │   │   ├── PIC24E.slaspec
│   │   │   ├── PIC24F.sla
│   │   │   ├── PIC24F.slaspec
│   │   │   ├── PIC24H.sla
│   │   │   └── PIC24H.slaspec
│   │   ├── PowerPC
│   │   │   ├── ppc_32_4xx_be.sla
│   │   │   ├── ppc_32_4xx_be.slaspec
│   │   │   ├── ppc_32_4xx_le.sla
│   │   │   ├── ppc_32_4xx_le.slaspec
│   │   │   ├── ppc_32_be_Mac.cspec
│   │   │   ├── ppc_32_be.sla
│   │   │   ├── ppc_32_be.slaspec
│   │   │   ├── ppc_32_e500_be.cspec
│   │   │   ├── ppc_32_e500_be.sla
│   │   │   ├── ppc_32_e500_be.slaspec
│   │   │   ├── ppc_32_e500_le.cspec
│   │   │   ├── ppc_32_e500_le.sla
│   │   │   ├── ppc_32_e500_le.slaspec
│   │   │   ├── ppc_32_e500mc_be.cspec
│   │   │   ├── ppc_32_e500mc_be.sla
│   │   │   ├── ppc_32_e500mc_be.slaspec
│   │   │   ├── ppc_32_e500mc_le.cspec
│   │   │   ├── ppc_32_e500mc_le.sla
│   │   │   ├── ppc_32_e500mc_le.slaspec
│   │   │   ├── ppc_32_le.sla
│   │   │   ├── ppc_32_le.slaspec
│   │   │   ├── ppc_32_mpc8270.pspec
│   │   │   ├── ppc_32_quicciii_be.sla
│   │   │   ├── ppc_32_quicciii_be.slaspec
│   │   │   ├── ppc_32_quicciii_le.sla
│   │   │   ├── ppc_32_quicciii_le.slaspec
│   │   │   ├── ppc_32.cspec
│   │   │   ├── ppc_32.pspec
│   │   │   ├── ppc_64_32.cspec
│   │   │   ├── ppc_64_be_Mac.cspec
│   │   │   ├── ppc_64_be.cspec
│   │   │   ├── ppc_64_be.sla
│   │   │   ├── ppc_64_be.slaspec
│   │   │   ├── ppc_64_isa_altivec_be.sla
│   │   │   ├── ppc_64_isa_altivec_be.slaspec
│   │   │   ├── ppc_64_isa_altivec_le.sla
│   │   │   ├── ppc_64_isa_altivec_le.slaspec
│   │   │   ├── ppc_64_isa_altivec_vle_be.sla
│   │   │   ├── ppc_64_isa_altivec_vle_be.slaspec
│   │   │   ├── ppc_64_isa_be.sla
│   │   │   ├── ppc_64_isa_be.slaspec
│   │   │   ├── ppc_64_isa_le.sla
│   │   │   ├── ppc_64_isa_le.slaspec
│   │   │   ├── ppc_64_isa_vle_be.sla
│   │   │   ├── ppc_64_isa_vle_be.slaspec
│   │   │   ├── ppc_64_le.cspec
│   │   │   ├── ppc_64_le.sla
│   │   │   ├── ppc_64_le.slaspec
│   │   │   ├── ppc_64.pspec
│   │   │   └── ppc.ldefs
│   │   ├── RISCV
│   │   │   ├── andestar_v5.ldefs
│   │   │   ├── andestar_v5.sla
│   │   │   ├── andestar_v5.slaspec
│   │   │   ├── riscv.ilp32d.sla
│   │   │   ├── riscv.ilp32d.slaspec
│   │   │   ├── riscv.ldefs
│   │   │   ├── riscv.lp64d.sla
│   │   │   ├── riscv.lp64d.slaspec
│   │   │   ├── riscv32-fp.cspec
│   │   │   ├── riscv32.cspec
│   │   │   ├── riscv64-fp.cspec
│   │   │   ├── riscv64.cspec
│   │   │   ├── RV32.pspec
│   │   │   └── RV64.pspec
│   │   ├── Sparc
│   │   │   ├── SparcV9_32.cspec
│   │   │   ├── SparcV9_32.sla
│   │   │   ├── SparcV9_32.slaspec
│   │   │   ├── SparcV9_64.cspec
│   │   │   ├── SparcV9_64.sla
│   │   │   ├── SparcV9_64.slaspec
│   │   │   ├── SparcV9.ldefs
│   │   │   └── SparcV9.pspec
│   │   ├── SuperH
│   │   │   ├── sh-1.sla
│   │   │   ├── sh-1.slaspec
│   │   │   ├── sh-2.sla
│   │   │   ├── sh-2.slaspec
│   │   │   ├── sh-2a.sla
│   │   │   ├── sh-2a.slaspec
│   │   │   ├── superh.cspec
│   │   │   ├── superh.ldefs
│   │   │   ├── superh.pspec
│   │   │   └── superh2a.cspec
│   │   ├── TriCore
│   │   │   ├── tc172x.pspec
│   │   │   ├── tc176x.pspec
│   │   │   ├── tc29x.pspec
│   │   │   ├── tricore.cspec
│   │   │   ├── tricore.ldefs
│   │   │   ├── tricore.pspec
│   │   │   ├── tricore.sla
│   │   │   └── tricore.slaspec
│   │   ├── V850
│   │   │   ├── V850.cspec
│   │   │   ├── V850.ldefs
│   │   │   ├── V850.pspec
│   │   │   ├── V850.sla
│   │   │   └── V850.slaspec
│   │   ├── x86
│   │   │   ├── x86-16-real.pspec
│   │   │   ├── x86-16.cspec
│   │   │   ├── x86-16.pspec
│   │   │   ├── x86-32-golang.cspec
│   │   │   ├── x86-64-compat32.pspec
│   │   │   ├── x86-64-gcc.cspec
│   │   │   ├── x86-64-golang.cspec
│   │   │   ├── x86-64-swift.cspec
│   │   │   ├── x86-64-win.cspec
│   │   │   ├── x86-64.pspec
│   │   │   ├── x86-64.sla
│   │   │   ├── x86-64.slaspec
│   │   │   ├── x86.ldefs
│   │   │   ├── x86.pspec
│   │   │   ├── x86.sla
│   │   │   ├── x86.slaspec
│   │   │   ├── x86borland.cspec
│   │   │   ├── x86delphi.cspec
│   │   │   ├── x86gcc.cspec
│   │   │   └── x86win.cspec
│   │   ├── Xtensa
│   │   │   ├── xtensa_be.sla
│   │   │   ├── xtensa_be.slaspec
│   │   │   ├── xtensa_le.sla
│   │   │   ├── xtensa_le.slaspec
│   │   │   ├── xtensa.cspec
│   │   │   ├── xtensa.ldefs
│   │   │   └── xtensa.pspec
│   │   └── Z80
│   │       ├── z180.pspec
│   │       ├── z180.sla
│   │       ├── z180.slaspec
│   │       ├── z182.pspec
│   │       ├── z80.cspec
│   │       ├── z80.ldefs
│   │       ├── z80.pspec
│   │       ├── z80.sla
│   │       ├── z80.slaspec
│   │       └── z8401x.pspec
│   ├── sourcemap
│   │   ├── DummySourceFileManager.cpp
│   │   └── SourcePathTransformRecord.cpp
│   ├── storage
│   │   ├── BranchManager.cpp
│   │   ├── CommitManager.cpp
│   │   ├── Event.cpp
│   │   ├── EventLog.cpp
│   │   ├── FksIndexManager.cpp
│   │   ├── FksRepository.cpp
│   │   ├── IndexManager.cpp
│   │   ├── Repository.cpp
│   │   ├── SnapshotReader.cpp
│   │   ├── SnapshotWriter.cpp
│   │   └── WorkingSnapshot.cpp
│   ├── symbol
│   │   ├── CodeUnit.cpp
│   │   ├── ExternalLocation.cpp
│   │   ├── ExternalLocationAdapter.cpp
│   │   ├── ExternalPath.cpp
│   │   ├── Function.cpp
│   │   ├── FunctionIterator.cpp
│   │   ├── FunctionSignatureImpl.cpp
│   │   ├── IllegalCharCppTransformer.cpp
│   │   ├── LabelHistory.cpp
│   │   ├── MemReferenceImpl.cpp
│   │   ├── Namespace.cpp
│   │   ├── PrototypeModel.cpp
│   │   ├── Reference.cpp
│   │   ├── ReferenceIteratorAdapter.cpp
│   │   ├── RefTypeFactory.cpp
│   │   ├── SourceFile.cpp
│   │   ├── Symbol.cpp
│   │   ├── SymbolIterator.cpp
│   │   ├── SymbolIteratorAdapter.cpp
│   │   ├── SymbolTable.cpp
│   │   ├── SymbolUtilities.cpp
│   │   ├── ThunkReference.cpp
│   │   └── Variable.cpp
│   ├── types
│   │   ├── AbstractColorDataType.cpp
│   │   ├── AbstractComplexDataType.cpp
│   │   ├── AbstractFloatDataType.cpp
│   │   ├── AbstractIntegerDataType.cpp
│   │   ├── AbstractLeb128DataType.cpp
│   │   ├── AbstractPointerTypedefBuiltIn.cpp
│   │   ├── AbstractSignedIntegerDataType.cpp
│   │   ├── AbstractStringDataType.cpp
│   │   ├── AbstractUnsignedIntegerDataType.cpp
│   │   ├── AIFFDataType.cpp
│   │   ├── AlignmentDataType.cpp
│   │   ├── AlignmentType.cpp
│   │   ├── ArrayDataType.cpp
│   │   ├── ArrayStringable.cpp
│   │   ├── AUDataType.cpp
│   │   ├── AudioPlayer.cpp
│   │   ├── BadDataType.cpp
│   │   ├── BitFieldDataType.cpp
│   │   ├── BitFieldPackingImpl.cpp
│   │   ├── BitmapResource.cpp
│   │   ├── BitmapResourceDataType.cpp
│   │   ├── BooleanDataType.cpp
│   │   ├── BuiltIn.cpp
│   │   ├── BuiltInDataTypeManager.cpp
│   │   ├── ByteDataType.cpp
│   │   ├── CharDataType.cpp
│   │   ├── CharsetSettingsDefinition.cpp
│   │   ├── ColorIcon.cpp
│   │   ├── Complex16DataType.cpp
│   │   ├── Complex32DataType.cpp
│   │   ├── Complex8DataType.cpp
│   │   ├── Composite.cpp
│   │   ├── CompositeAlignmentHelper.cpp
│   │   ├── CompositeDataTypeImpl.cpp
│   │   ├── CountedDynamicDataType.cpp
│   │   ├── CustomFormat.cpp
│   │   ├── DataImage.cpp
│   │   ├── DataTypeArchiveIdDumper.cpp
│   │   ├── DataTypeComparator.cpp
│   │   ├── DataTypeComponentImpl.cpp
│   │   ├── DataTypeDisplayOptions.cpp
│   │   ├── DataTypeImpl.cpp
│   │   ├── DataTypeInstance.cpp
│   │   ├── DataTypeManagerDomainObject.cpp
│   │   ├── DataTypeNameComparator.cpp
│   │   ├── DataTypeObjectComparator.cpp
│   │   ├── DataTypePath.cpp
│   │   ├── DataTypeSymbol.cpp
│   │   ├── DataTypeUtilities.cpp
│   │   ├── DataTypeWithCharset.cpp
│   │   ├── DataUtilities.cpp
│   │   ├── DefaultDataType.cpp
│   │   ├── DialogResourceDataType.cpp
│   │   ├── DoubleComplexDataType.cpp
│   │   ├── DoubleDataType.cpp
│   │   ├── DWordDataType.cpp
│   │   ├── DynamicDataType.cpp
│   │   ├── EnumDataType.cpp
│   │   ├── FactoryStructureDataType.cpp
│   │   ├── FileArchiveBasedDataTypeManager.cpp
│   │   ├── FileDataTypeManager.cpp
│   │   ├── FileTimeDataType.cpp
│   │   ├── Float10DataType.cpp
│   │   ├── Float16DataType.cpp
│   │   ├── Float2DataType.cpp
│   │   ├── Float4DataType.cpp
│   │   ├── Float8DataType.cpp
│   │   ├── FloatComplexDataType.cpp
│   │   ├── FloatDataType.cpp
│   │   ├── FunctionDefinitionDataType.cpp
│   │   ├── GenericDataType.cpp
│   │   ├── GifDataType.cpp
│   │   ├── GIFResource.cpp
│   │   ├── IBO32DataType.cpp
│   │   ├── IBO64DataType.cpp
│   │   ├── IconMaskResourceDataType.cpp
│   │   ├── IconResource.cpp
│   │   ├── IconResourceDataType.cpp
│   │   ├── IndexedDynamicDataType.cpp
│   │   ├── Integer16DataType.cpp
│   │   ├── Integer3DataType.cpp
│   │   ├── Integer5DataType.cpp
│   │   ├── Integer6DataType.cpp
│   │   ├── Integer7DataType.cpp
│   │   ├── IntegerDataType.cpp
│   │   ├── JPEGDataType.cpp
│   │   ├── LongDataType.cpp
│   │   ├── LongDoubleComplexDataType.cpp
│   │   ├── LongDoubleDataType.cpp
│   │   ├── LongLongDataType.cpp
│   │   ├── MacintoshTimeStampDataType.cpp
│   │   ├── MemBufferImageInputStream.cpp
│   │   ├── MenuResourceDataType.cpp
│   │   ├── MetaDataType.cpp
│   │   ├── MIDIDataType.cpp
│   │   ├── MissingBuiltInDataType.cpp
│   │   ├── OpBehavior.cpp
│   │   ├── PackingType.cpp
│   │   ├── ParameterDefinitionImpl.cpp
│   │   ├── PartialUnion.cpp
│   │   ├── PascalString255DataType.cpp
│   │   ├── PascalStringDataType.cpp
│   │   ├── PascalUnicodeDataType.cpp
│   │   ├── Playable.cpp
│   │   ├── PngDataType.cpp
│   │   ├── PngResource.cpp
│   │   ├── Pointer16DataType.cpp
│   │   ├── Pointer24DataType.cpp
│   │   ├── Pointer32DataType.cpp
│   │   ├── Pointer40DataType.cpp
│   │   ├── Pointer48DataType.cpp
│   │   ├── Pointer56DataType.cpp
│   │   ├── Pointer64DataType.cpp
│   │   ├── Pointer8DataType.cpp
│   │   ├── PointerDataType.cpp
│   │   ├── PointerTypedef.cpp
│   │   ├── PointerTypedefBuilder.cpp
│   │   ├── ProgramArchitectureTranslator.cpp
│   │   ├── ProjectArchiveBasedDataTypeManager.cpp
│   │   ├── QWordDataType.cpp
│   │   ├── ReadOnlyDataTypeComponent.cpp
│   │   ├── RenderUnicodeSettingsDefinition.cpp
│   │   ├── RepeatCountDataType.cpp
│   │   ├── RepeatedDynamicDataType.cpp
│   │   ├── RepeatedStringDataType.cpp
│   │   ├── Resource.cpp
│   │   ├── RGB16ColorDataType.cpp
│   │   ├── RGB32ColorDataType.cpp
│   │   ├── ScorePlayer.cpp
│   │   ├── SegmentedCodePointerDataType.cpp
│   │   ├── ShiftedAddressDataType.cpp
│   │   ├── ShortDataType.cpp
│   │   ├── SignedByteDataType.cpp
│   │   ├── SignedCharDataType.cpp
│   │   ├── SignedDWordDataType.cpp
│   │   ├── SignedLeb128DataType.cpp
│   │   ├── SignedQWordDataType.cpp
│   │   ├── SignedWordDataType.cpp
│   │   ├── SourceArchiveImpl.cpp
│   │   ├── StandAloneDataTypeManager.cpp
│   │   ├── StringDataInstance.cpp
│   │   ├── StringDataType.cpp
│   │   ├── StringLayoutEnum.cpp
│   │   ├── StringRenderBuilder.cpp
│   │   ├── StringRenderParser.cpp
│   │   ├── StringUTF8DataType.cpp
│   │   ├── StructureDataType.cpp
│   │   ├── StructuredDynamicDataType.cpp
│   │   ├── StructureFactory.cpp
│   │   ├── TerminatedStringDataType.cpp
│   │   ├── TerminatedUnicode32DataType.cpp
│   │   ├── TerminatedUnicodeDataType.cpp
│   │   ├── TranslationSettingsDefinition.cpp
│   │   ├── TypedefDataType.cpp
│   │   ├── Undefined.cpp
│   │   ├── Undefined1DataType.cpp
│   │   ├── Undefined2DataType.cpp
│   │   ├── Undefined3DataType.cpp
│   │   ├── Undefined4DataType.cpp
│   │   ├── Undefined5DataType.cpp
│   │   ├── Undefined6DataType.cpp
│   │   ├── Undefined7DataType.cpp
│   │   ├── Undefined8DataType.cpp
│   │   ├── Unicode32DataType.cpp
│   │   ├── UnicodeDataType.cpp
│   │   ├── UnionDataType.cpp
│   │   ├── UnsignedCharDataType.cpp
│   │   ├── UnsignedInteger16DataType.cpp
│   │   ├── UnsignedInteger3DataType.cpp
│   │   ├── UnsignedInteger5DataType.cpp
│   │   ├── UnsignedInteger6DataType.cpp
│   │   ├── UnsignedInteger7DataType.cpp
│   │   ├── UnsignedIntegerDataType.cpp
│   │   ├── UnsignedLeb128DataType.cpp
│   │   ├── UnsignedLongDataType.cpp
│   │   ├── UnsignedLongLongDataType.cpp
│   │   ├── UnsignedShortDataType.cpp
│   │   ├── VoidDataType.cpp
│   │   ├── WAVEDataType.cpp
│   │   ├── WideChar16DataType.cpp
│   │   ├── WideChar32DataType.cpp
│   │   ├── WideCharDataType.cpp
│   │   └── WordDataType.cpp
│   └── util
│       ├── datastruct
│       │   ├── Range.cpp
│       │   ├── RedBlackEntry.cpp
│       │   ├── RedBlackTree.cpp
│       │   └── SortedRangeList.cpp
│       ├── graph
│       │   ├── DepthFirstSearch.cpp
│       │   ├── DirectedGraph.cpp
│       │   ├── Dominator.cpp
│       │   ├── Edge.cpp
│       │   └── Vertex.cpp
│       ├── AcyclicCallGraphBuilder.cpp
│       ├── AndQuery.cpp
│       ├── CharsetInfo.cpp
│       ├── CharsetInfoManager.cpp
│       ├── DefaultIntPropertyMap.cpp
│       ├── DefaultPropertyMap.cpp
│       ├── Fixup.cpp
│       ├── LEB128.cpp
│       ├── LongIterator.cpp
│       ├── MemoryByteIterator.cpp
│       ├── NoSettings.cpp
│       ├── NumericUtilities.cpp
│       ├── OrQuery.cpp
│       ├── ProgramChangeRecord.cpp
│       ├── PropertySet.cpp
│       ├── Query.cpp
│       ├── StringUtilities.cpp
│       └── SymbolPath.cpp
├── test_binaries
│   ├── aarch64_dyn_stripped.elf
│   ├── notepad_test.exe
│   ├── shell32_test.dll
│   └── x64_dyn_stripped.elf
├── Testing
│   └── Temporary
│       └── CTestCostData.txt
├── tests
│   ├── __pycache__
│   │   └── test_corpus_regression.cpython-311.pyc
│   ├── corpus
│   │   ├── expected
│   │   │   ├── aarch64_fib.elf.c
│   │   │   ├── aarch64_pie_dyn.elf.c
│   │   │   ├── arith.bin.c
│   │   │   ├── arm_dyn.elf.c
│   │   │   ├── arm32_fib.elf.c
│   │   │   ├── avx.bin.c
│   │   │   ├── branch_test.bin.c
│   │   │   ├── call_test.bin.c
│   │   │   ├── crypto.bin.c
│   │   │   ├── float_arith.bin.c
│   │   │   ├── float_cmp.bin.c
│   │   │   ├── jmptail.bin.c
│   │   │   ├── large_x86_64.elf.c
│   │   │   ├── mips_dyn.elf.c
│   │   │   ├── mipsel_fib.elf.c
│   │   │   ├── nopfall.bin.c
│   │   │   ├── pe_test.bin.c
│   │   │   ├── ppc_dyn.elf.c
│   │   │   ├── ppc32_fib.elf.c
│   │   │   ├── ret.bin.c
│   │   │   ├── simd_float.bin.c
│   │   │   ├── simd_int.bin.c
│   │   │   ├── simple.bin.c
│   │   │   ├── stackframe.bin.c
│   │   │   ├── x64_dyn.elf.c
│   │   │   └── zerotail.bin.c
│   │   ├── ghidra_listing
│   │   │   ├── aarch64_fib_enigma.csv
│   │   │   ├── aarch64_fib.elf_enigma.csv
│   │   │   ├── aarch64_fib.elf.csv
│   │   │   ├── aarch64_pie_dyn.elf_enigma_export_check.csv
│   │   │   ├── aarch64_pie_dyn.elf_enigma_recheck.csv
│   │   │   ├── aarch64_pie_dyn.elf_enigma.csv
│   │   │   ├── aarch64_pie_dyn.elf.csv
│   │   │   ├── arm_dyn.elf_enigma_export_check.csv
│   │   │   ├── arm_dyn.elf_enigma_recheck.csv
│   │   │   ├── arm_dyn.elf_enigma.csv
│   │   │   ├── arm_dyn.elf.csv
│   │   │   ├── arm32_fib.elf_enigma.csv
│   │   │   ├── arm32_fib.elf.csv
│   │   │   ├── large_x86_64.elf_enigma.csv
│   │   │   ├── large_x86_64.elf.csv
│   │   │   ├── mips_dyn.elf_enigma.csv
│   │   │   ├── mips_dyn.elf.csv
│   │   │   ├── mipsel_fib.elf_enigma.csv
│   │   │   ├── mipsel_fib.elf.csv
│   │   │   ├── ppc_dyn.elf_enigma.csv
│   │   │   ├── ppc_dyn.elf.csv
│   │   │   ├── ppc32_fib.elf_enigma.csv
│   │   │   ├── ppc32_fib.elf.csv
│   │   │   ├── x64_dyn_stripped_enigma.csv
│   │   │   ├── x64_dyn_stripped.elf.csv
│   │   │   ├── x64_dyn.elf_enigma.csv
│   │   │   └── x64_dyn.elf.csv
│   │   ├── aarch64_fib.elf
│   │   ├── aarch64_pie_dyn.elf
│   │   ├── arith.bin
│   │   ├── arm_dyn.elf
│   │   ├── arm32_fib.elf
│   │   ├── avx.bin
│   │   ├── branch_test.bin
│   │   ├── call_test.bin
│   │   ├── crypto.bin
│   │   ├── float_arith.bin
│   │   ├── float_cmp.bin
│   │   ├── large_x86_64.elf
│   │   ├── mips_dyn.elf
│   │   ├── mipsel_fib.elf
│   │   ├── ppc_dyn.elf
│   │   ├── ppc32_fib.elf
│   │   ├── simd_float.bin
│   │   ├── simd_int.bin
│   │   ├── stackframe.bin
│   │   └── x64_dyn.elf
│   ├── headless_proj
│   │   ├── decomp_a64pie_20261025152322.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── decomp_large_20261025152734.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── decomp_x64dyn_20261025152255.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── decomp20261023012459.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── parity20261005210656.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── parity20261005210746.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   ├── ~00000001.db
│   │   │   │   │   ├── ~00000002.db
│   │   │   │   │   ├── ~00000003.db
│   │   │   │   │   ├── ~00000004.db
│   │   │   │   │   ├── ~00000005.db
│   │   │   │   │   ├── ~00000006.db
│   │   │   │   │   ├── ~00000007.db
│   │   │   │   │   ├── ~00000008.db
│   │   │   │   │   ├── ~00000009.db
│   │   │   │   │   ├── 00000000.prp
│   │   │   │   │   ├── 00000001.prp
│   │   │   │   │   ├── 00000002.prp
│   │   │   │   │   ├── 00000003.prp
│   │   │   │   │   ├── 00000004.prp
│   │   │   │   │   ├── 00000005.prp
│   │   │   │   │   ├── 00000006.prp
│   │   │   │   │   ├── 00000007.prp
│   │   │   │   │   ├── 00000008.prp
│   │   │   │   │   └── 00000009.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── parity20261005213550.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   ├── ~00000001.db
│   │   │   │   │   ├── ~00000002.db
│   │   │   │   │   ├── ~00000003.db
│   │   │   │   │   ├── ~00000004.db
│   │   │   │   │   ├── ~00000005.db
│   │   │   │   │   ├── ~00000006.db
│   │   │   │   │   ├── ~00000007.db
│   │   │   │   │   ├── ~00000008.db
│   │   │   │   │   ├── ~00000009.db
│   │   │   │   │   ├── 00000000.prp
│   │   │   │   │   ├── 00000001.prp
│   │   │   │   │   ├── 00000002.prp
│   │   │   │   │   ├── 00000003.prp
│   │   │   │   │   ├── 00000004.prp
│   │   │   │   │   ├── 00000005.prp
│   │   │   │   │   ├── 00000006.prp
│   │   │   │   │   ├── 00000007.prp
│   │   │   │   │   ├── 00000008.prp
│   │   │   │   │   └── 00000009.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── smokeproj.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── smokeproj2.rep
│   │   │   ├── idata
│   │   │   │   ├── 00
│   │   │   │   │   ├── ~00000000.db
│   │   │   │   │   └── 00000000.prp
│   │   │   │   ├── ~index.bak
│   │   │   │   ├── ~index.dat
│   │   │   │   └── ~journal.bak
│   │   │   ├── user
│   │   │   │   └── ~index.dat
│   │   │   ├── versioned
│   │   │   │   ├── ~index.bak
│   │   │   │   └── ~index.dat
│   │   │   └── project.prp
│   │   ├── decomp_a64pie_20261025152322.gpr
│   │   ├── decomp_large_20261025152734.gpr
│   │   ├── decomp_x64dyn_20261025152255.gpr
│   │   ├── decomp20261023012459.gpr
│   │   ├── parity20261005210656.gpr
│   │   ├── parity20261005210746.gpr
│   │   ├── parity20261005213550.gpr
│   │   ├── smokeproj.gpr
│   │   └── smokeproj2.gpr
│   ├── audit_type_propagation.py
│   ├── regenerate_corpus.py
│   ├── test_aarch64_pipeline.cpp
│   ├── test_analyzer_integration.cpp
│   ├── test_apply_known_signature.cpp
│   ├── test_assembler_patching.cpp
│   ├── test_batch_aa.cpp
│   ├── test_batch_ab.cpp
│   ├── test_batch_e.cpp
│   ├── test_batch_f.cpp
│   ├── test_batch_g.cpp
│   ├── test_batch_h.cpp
│   ├── test_batch_i.cpp
│   ├── test_batch_j.cpp
│   ├── test_batch_k.cpp
│   ├── test_batch_l.cpp
│   ├── test_batch_n.cpp
│   ├── test_batch_o.cpp
│   ├── test_batch_p.cpp
│   ├── test_batch_q.cpp
│   ├── test_batch_r.cpp
│   ├── test_batch_s.cpp
│   ├── test_batch_t.cpp
│   ├── test_batch_u.cpp
│   ├── test_batch_v.cpp
│   ├── test_batch_w.cpp
│   ├── test_batch_x.cpp
│   ├── test_batch_y.cpp
│   ├── test_batch_z.cpp
│   ├── test_block_struct.cpp
│   ├── test_cli_regression.py
│   ├── test_coff_loader.cpp
│   ├── test_compile.cpp
│   ├── test_corpus_regression.py
│   ├── test_datatype_merger.cpp
│   ├── test_decomp_interface.cpp
│   ├── test_decompiler_stress.cpp
│   ├── test_decompiler.cpp
│   ├── test_determinism_regression.py
│   ├── test_disasm_cfg.cpp
│   ├── test_elf_compiler_detect.cpp
│   ├── test_elf_dyn_overlap.cpp
│   ├── test_elf_pltgot.cpp
│   ├── test_firmware_loader.cpp
│   ├── test_fks_fingerprint.cpp
│   ├── test_fks_index.cpp
│   ├── test_fks_library.cpp
│   ├── test_function_boundaries.cpp
│   ├── test_function_graph.cpp
│   ├── test_gap_verification.cpp
│   ├── test_gbf_reader.cpp
│   ├── test_gnu_build_attributes.cpp
│   ├── test_golang_pipeline.cpp
│   ├── test_gui_smoke.cpp
│   ├── test_gzf_equates.cpp
│   ├── test_gzf_fidelity.cpp
│   ├── test_gzf_function_tags.cpp
│   ├── test_gzf_import.cpp
│   ├── test_gzf_rebase.cpp
│   ├── test_headless_suite.cpp
│   ├── test_lang_classes.cpp
│   ├── test_loader.cpp
│   ├── test_macho_loader.cpp
│   ├── test_mips16_context.cpp
│   ├── test_objc_backend.cpp
│   ├── test_patching_features.cpp
│   ├── test_pdb_parser.cpp
│   ├── test_pe_loader.cpp
│   ├── test_pipeline_comprehensive.cpp
│   ├── test_pipeline.cpp
│   ├── test_repository_reload.cpp
│   ├── test_rust_strings_backend.cpp
│   ├── test_signature_persistence.cpp
│   ├── test_storage_phase1.cpp
│   ├── test_storage_phase2.cpp
│   ├── test_storage_phase3.cpp
│   ├── test_storage_phase4.cpp
│   ├── test_storage_phase5.cpp
│   ├── test_swift_backend.cpp
│   └── test_type_roundtrip.cpp
├── tools
│   ├── ghidra
│   │   └── EnigmaExportFidMatches.java
│   ├── ghidra_exports
│   │   ├── advapi32_export.json
│   │   ├── bcryptprimitives_export.json
│   │   ├── cfgmgr32_export.json
│   │   ├── combase_export.json
│   │   ├── comctl32_export.json
│   │   ├── crypt32_export.json
│   │   ├── d3d11_export.json
│   │   ├── devobj_export.json
│   │   ├── dwrite_export.json
│   │   ├── dxgi_export.json
│   │   ├── gdi32_export.json
│   │   ├── gdi32full_export.json
│   │   ├── iertutil_export.json
│   │   ├── kernelbase_export.json
│   │   ├── mlang_export.json
│   │   ├── msvcp_win_export.json
│   │   ├── netapi32_export.json
│   │   ├── ntmarta_export.json
│   │   ├── ole32_export.json
│   │   ├── oleaut32_export.json
│   │   ├── profapi_export.json
│   │   ├── rpcrt4_export.json
│   │   ├── sechost_export.json
│   │   ├── shlwapi_export.json
│   │   ├── urlmon_export.json
│   │   ├── userenv_export.json
│   │   ├── uxtheme_export.json
│   │   ├── WindowsCodecs_export.json
│   │   ├── winhttp_export.json
│   │   ├── wininet_export.json
│   │   └── ws2_32_export.json
│   ├── ghidra_scripts
│   │   ├── EnigmaExportFidMatches.java
│   │   └── EnigmaOptimizeAnalysis.java
│   ├── headless
│   │   ├── DumpDecompile.java
│   │   └── DumpListing.java
│   ├── batch_ghidra_ingest.ps1
│   ├── batch_optimized_ghidra_export.ps1
│   ├── build_enigma.ps1
│   ├── check_nop_patterns.py
│   ├── check_pdata.py
│   ├── classify_extras.py
│   ├── classify_missing.py
│   ├── classify_noisefix.py
│   ├── compare_function_lists.py
│   ├── compare_naming.py
│   ├── crt_classification_snippet.cpp
│   ├── debug_rexfix.py
│   ├── debug_sections.py
│   ├── dump_all_missing.py
│   ├── dump_missing_bytes.py
│   ├── en_singles.py
│   ├── enigma_binary_audit.cpp
│   ├── enigma_decompile_full.cpp
│   ├── enigma_decompile.cpp
│   ├── enigma_dump_functions.cpp
│   ├── enigma_dump_listing.cpp
│   ├── enigma_fingerprint_audit.cpp
│   ├── enigma_fks_build_index.cpp
│   ├── enigma_fks_export_hashes.cpp
│   ├── enigma_fks_ingest_from_ghidra.cpp
│   ├── enigma_fks_ingest.cpp
│   ├── enigma_gzf_inspect.cpp
│   ├── enigma_gzf_probe.cpp
│   ├── enigma_naming_audit.cpp
│   ├── enigma_patch_cli.cpp
│   ├── enigma_pipeline_audit.cpp
│   ├── evaluate_cross_library.cpp
│   ├── evaluate_graph_matching.cpp
│   ├── evaluate_id_rate_from_fkslib.cpp
│   ├── evaluate_id_rate.cpp
│   ├── final_survey.cpp
│   ├── find_no_relations.cpp
│   ├── FORENSIC_714_REPORT.md
│   ├── forensic_714.py
│   ├── gen_signatures.py
│   ├── generate_ghidra_csvs.py
│   ├── ghidra_dump_functions.java
│   ├── ghidra_dump_functions.jy
│   ├── ghidra_dump_functions.py
│   ├── ghidra_env.ps1
│   ├── ghidra_raw_output.txt
│   ├── investigate_missing_funcs.py
│   ├── investigate_missing_part2.py
│   ├── investigate_missing.py
│   ├── investigate_ntdll_func_data.py
│   ├── list_ghidra_status.cpp
│   ├── migrate_all_to_v3.ps1
│   ├── migrate_remaining.ps1
│   ├── parity_decomp_diff.py
│   ├── parity_listing_diff.py
│   ├── pe_debug.py
│   ├── phase_a_ingest.ps1
│   ├── phase_b_experiment.py
│   ├── phase4_sampling.py
│   ├── phase5_funcstart.py
│   ├── phase5b_inside_check.py
│   ├── phase5c_preceding_bytes.py
│   ├── phase5c_preceding.py
│   ├── rebuild_fks_index.cpp
│   ├── reingest_arm64.ps1
│   ├── remigrate_no_relations.ps1
│   ├── remigrate_skip_large.ps1
│   ├── report_stats.py
│   ├── run_decomp_audit.ps1
│   ├── run_parity_audit.ps1
│   ├── stress_test_runner.py
│   ├── survey_fkslibs.cpp
│   ├── survey_v3_status.cpp
│   ├── verify_pdata.py
│   └── vtable_analysis.py
├── CMakeLists.txt
├── debug_repro.exe
├── debug_snap.exe
├── jmptail.bin
├── nopfall.bin
├── out.csv
├── ret.bin
├── simple.bin
└── zerotail.bin
```
