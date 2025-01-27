```mermaid
grapg TD
    CPPValueType[CPP值类型]
    Collections[数据结构]
    PythonObject[Python对象]

    CPPValueType --方法--> Collections
    Collections --调试信息--> CPP值类型
    Collections --构造函数--> PythonObject
    PythonObject --取出成员用以生成调试信息--> Collections
    CPPValueType --快速创建对象(通过Collections)--> PythonObject
    PythonObject --生成调试信息 或者 序列化--> Collections

```