#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "ByteCode/PyInst.h"
#include "Object/Klass.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class PyCode;

using PyCodePtr = std::shared_ptr<PyCode>;
enum class Scope { ERR = 0, LOCAL, GLOBAL, Closure };
class PyCode : public PyObject {
  friend class CodeKlass;

 public:
  explicit PyCode(
    const PyObjPtr& byteCodes,
    const PyObjPtr& consts,
    const PyObjPtr& names,
    const PyObjPtr& varNames,
    const PyObjPtr& name,
    Index nLocals
  );

  [[nodiscard]] PyListPtr Instructions();

  void SetInstructions(const PyListPtr& insts);

  void SetByteCode(const PyBytesPtr& byteCodes);

  void SetNLocals(Index nLocals);

  void SetScope(Scope scope);

  PyBytesPtr ByteCode() const;

  [[nodiscard]] PyListPtr Consts() const;

  [[nodiscard]] PyListPtr Names() const;

  [[nodiscard]] PyStrPtr Name() const;

  [[nodiscard]] PyListPtr VarNames() const;

  [[nodiscard]] Index NLocals() const;

  [[nodiscard]] Scope Scope() const;

  Index IndexOfConst(const PyObjPtr& obj);

  void RegisterConst(const PyObjPtr& obj);

  Index IndexOfName(const PyObjPtr& name);

  void RegisterName(const PyObjPtr& name);

  Index IndexOfVarName(const PyObjPtr& name);

  void RegisterVarName(const PyObjPtr& name);

  /**
   * @param obj 可以是String, Integer, Float, Boolean, None, List，Code
   */
  void LoadConst(const PyObjPtr& obj) {
    auto index = IndexOfConst(obj);
    instructions->Append(CreateLoadConst(index));
  }

  void LoadName(const PyObjPtr& obj) {
    auto index = IndexOfName(obj);
    instructions->Append(CreateLoadName(index));
  }

  void StoreName(const PyObjPtr& obj) {
    auto index = IndexOfName(obj);
    instructions->Append(CreateStoreName(index));
  }

  void LoadAttr(const PyObjPtr& obj) {
    auto index = IndexOfName(obj);
    instructions->Append(CreateLoadAttr(index));
  }

  void LoadGlobal(const PyObjPtr& obj) {
    auto index = IndexOfName(obj);
    instructions->Append(CreateLoadGlobal(index));
  }

  void LoadFast(const PyObjPtr& obj) {
    auto index = IndexOfVarName(obj);
    instructions->Append(CreateLoadFast(index));
  }

  void StoreFast(const PyObjPtr& obj) {
    auto index = IndexOfVarName(obj);
    instructions->Append(CreateStoreFast(index));
  }

  void BuildList(Index size) { instructions->Append(CreateBuildList(size)); }
  void BuildSlice() { instructions->Append(CreateBuildSlice()); }

  void CallFunction(Index nArgs);

  void MakeFunction();

  void ReturnValue();
  Index PopJumpIfFalse();
  Index JumpForward() {
    instructions->Append(CreateJumpForward(0));
    return instructions->Length();
  }
  void JumpAbsolute(Index index);
  void PopTop();
  void StoreSubscr();
  void GetIter();
  Index ForIter(Index index);
  void LoadBuildClass();
  void StoreAttr(const PyObjPtr& obj);
  void Nop();
  void UnaryPositive();
  void UnaryNegative();
  void UnaryNot();
  void UnaryInvert();
  void BinaryPower();
  void BinaryModulo();
  void BinaryFloorDivide();
  void BinaryTrueDivide();
  void BinaryLShift();
  void BinaryRShift();
  void BinaryAnd();
  void BinaryXor();
  void BinaryOr();
  void YieldValue() { instructions->Append(CreateYieldValue()); }

 private:
  PyBytesPtr byteCode;
  PyListPtr instructions;
  PyListPtr consts;
  PyListPtr names;
  PyListPtr varNames;
  PyStrPtr name;
  Index nLocals;
  enum Scope scope = Scope::ERR;
};

using PyCodePtr = std::shared_ptr<PyCode>;

class CodeKlass : public Klass {
 public:
  explicit CodeKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<CodeKlass>();
    LoadClass(CreatePyString("code")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  PyObjPtr repr(const PyObjPtr& self) override;

  PyObjPtr _serialize_(const PyObjPtr& self) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};

PyObjPtr CreatePyCode(const PyObjPtr& name);
// 打印PyCode的详细信息
void PrintCode(const PyCodePtr& code);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
