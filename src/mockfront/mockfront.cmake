set(module_name "mockfront")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_mock_frontend_files ${torchlight_mock_frontend_files} ${torchlight_${module_name}_files})