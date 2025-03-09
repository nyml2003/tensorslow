#include "Object/PySlice.h"
namespace torchlight::Object {
/*
def slice_data(data, start=None, stop=None, step=None):
    """
    对列表进行切片操作，并支持类型检查和边界处理。

    参数:
        data (list): 要处理的列表数据。
        start (int, optional): 切片的起始索引。默认为 None。
        stop (int, optional): 切片的结束索引。默认为 None。
        step (int, optional): 切片的步长。默认为 None。

    返回:
        list: 切片后的结果。

    异常:
        TypeError: 如果输入的 data 不是列表，或者 start/stop/step 的类型不正确。
        ValueError: 如果 step 为 0。
    """
    # 类型检查
    if not isinstance(data, list):
        raise TypeError("data 必须是一个列表。")
    if start is not None and not isinstance(start, int):
        raise TypeError("start 必须是整数或 None。")
    if stop is not None and not isinstance(stop, int):
        raise TypeError("stop 必须是整数或 None。")
    if step is not None and not isinstance(step, int):
        raise TypeError("step 必须是整数或 None。")
    if step == 0:
        raise ValueError("step 不能为 0。")

    # 获取列表长度
    list_length = len(data)

    # 处理 start 参数
    if start is None:
        start = 0 if step is None or step > 0 else list_length - 1
    else:
        start = start if start >= 0 else list_length + start
        start = max(0, min(start, list_length - 1))

    # 处理 stop 参数
    if stop is None:
        stop = list_length if step is None or step > 0 else -1
    else:
        stop = stop if stop >= 0 else list_length + stop
        stop = max(0, min(stop, list_length))

    # 处理 step 参数
    if step is None:
        step = 1

    # 执行切片操作
    try:
        result = data[start:stop:step]
    except Exception as e:
        raise RuntimeError(f"切片操作失败：{e}")

    return result
*/
// void PySlice::CleanData(Index length) {
//   Index start = 0;
//   Index stop = length;
//   Index step = 1;
//   if (!this->start->is<PyNone>() && !this->start->is<PyInteger>()) {
//     auto errorMsg = StringConcat(CreatePyList(
//       {CreatePyString("start 必须是整数或 None。"),
//        this->start->str()->as<PyString>()}
//     ));
//     throw std::runtime_error(errorMsg->as<PyString>()->ToCppString());
//   }
//   if (this->start->is<PyInteger>()) {
//     start = this->start->as<PyInteger>()->ToU64();
//     start = start >= 0 ? start : length + start;
//     start = std::max(0, std::min(start, length - 1));
//   }
// }

}  // namespace torchlight::Object