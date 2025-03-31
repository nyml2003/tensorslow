#ifndef TORCHLIGHT_OBJECT_PYCODE_H
#define TORCHLIGHT_OBJECT_PYCODE_H

#include "Function/ObjectHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/Klass.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"
#include "Object/Runtime/PyInst.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

class PyCode;

using PyCodePtr = std::shared_ptr<PyCode>;
enum class Scope { ERR = 0, LOCAL, GLOBAL, Closure };
class PyCode : public PyObject {
  friend class CodeKlass;

 public:
  explicit PyCode(
    PyBytesPtr byteCodes,
    PyListPtr consts,
    PyListPtr names,
    PyListPtr varNames,
    PyStrPtr name,
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

  [[nodiscard]] Scope GetScope() const;

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
  void BuildMap(Index size) { instructions->Append(CreateBuildMap(size)); }
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
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("code")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }

  PyObjPtr repr(const PyObjPtr& self) override;

  PyObjPtr _serialize_(const PyObjPtr& self) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};

PyObjPtr CreatePyCode(const PyStrPtr& name);
// 打印PyCode的详细信息
void PrintCode(const PyCodePtr& code);
inline PyObjPtr CreatePyCode(
  const PyBytesPtr& byteCode,
  const PyListPtr& consts,
  const PyListPtr& names,
  const PyListPtr& varNames,
  const PyStrPtr& name,
  Index nLocals
) {
  return std::make_shared<PyCode>(
    byteCode, consts, names, varNames, name, nLocals
  );
}

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
