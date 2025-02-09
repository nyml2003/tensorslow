#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "Object/Klass.h"
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
  void LoadConst(const PyObjPtr& obj);

  void LoadName(const PyObjPtr& obj);

  void StoreName(const PyObjPtr& obj);

  void LoadAttr(const PyObjPtr& obj);

  void LoadGlobal(Index index);

  void LoadFast(Index index);

  void StoreFast(const PyObjPtr& obj);

  void BuildList(Index size);

  void CallFunction(Index nArgs);

  void MakeFunction();

  void ReturnValue();

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
  explicit CodeKlass();
  static KlassPtr Self();

  PyObjPtr repr(PyObjPtr self) override;

  PyObjPtr str(PyObjPtr self) override;

  PyObjPtr _serialize_(PyObjPtr self) override;

  void Initialize() override;
};

PyObjPtr CreatePyCode(const PyObjPtr& name);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
