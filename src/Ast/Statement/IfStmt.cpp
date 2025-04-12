#include "Ast/Statement/IfStmt.h"
#include "Ast/INode.h"
#include "Function/BuiltinFunction.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Number/PyInteger.h"
#include "Object/Runtime/PyInst.h"
#include "Object/String/PyString.h"

namespace torchlight::Ast {

Object::PyObjPtr IfStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<IfStmt>();
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  auto elseStmts = stmt->ElseStmts();
  auto elifs = stmt->Elifs();
  auto elifConditions = stmt->ElifConditions();
  condition->visit(codeList);
  Object::ForEach(thenStmts, [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->visit(codeList);
  });
  Object::ForEach(elifConditions, [&codeList](const Object::PyObjPtr& elif) {
    elif->as<INode>()->visit(codeList);
  });
  Object::ForEach(elifs, [&codeList](const Object::PyObjPtr& elif) {
    auto elifStms = elif;
    Object::ForEach(elifStms, [&codeList](const Object::PyObjPtr& stmt) {
      stmt->as<INode>()->visit(codeList);
    });
  });
  Object::ForEach(elseStmts, [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->visit(codeList);
  });

  return Object::CreatePyNone();
}

Object::PyObjPtr IfStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<IfStmt>();
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  auto elseStmts = stmt->ElseStmts();
  auto elifs = stmt->Elifs();
  auto elifConditions = stmt->ElifConditions();
  auto code = GetCodeFromList(codeList, stmt);

  // 生成条件的字节码
  condition->emit(codeList);
  // 添加 POP_JUMP_IF_FALSE 指令，跳转位置暂定
  Index thenConditionEnd = code->PopJumpIfFalse();

  // 生成 then 块的字节码
  Object::ForEach(thenStmts, [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->emit(codeList);
  });
  // then 块结束后，添加 JUMP_FORWARD 跳转到整个 if 结束的位置
  Index thenBlockEnd = code->JumpForward();
  code->Instructions()->SetItem(
    thenConditionEnd - 1, Object::CreatePopJumpIfFalse(static_cast<int64_t>(
                            thenBlockEnd - thenConditionEnd + 1
                          ))
  );
  Collections::List<Index> elifBlockEnds;
  // 处理 elif 部分
  for (Index i = 0; i < elifConditions->Length(); ++i) {
    auto elifCondition = elifConditions->GetItem(i);
    auto elifBlock = elifs->GetItem(i);

    // 生成 elif 条件的字节码
    elifCondition->as<Ast::INode>()->emit(codeList);
    // 添加 POP_JUMP_IF_FALSE 指令，跳转位置暂定
    Index elfiConditionEnd = code->PopJumpIfFalse();

    // 生成 elif 块的字节码
    auto elifStms = elifBlock;
    Object::ForEach(elifStms, [&codeList](const Object::PyObjPtr& stmt) {
      stmt->as<Ast::INode>()->emit(codeList);
    });
    // elif 块结束后，添加 JUMP_FORWARD 跳转到整个 if 结束的位置
    Index elifBlockEnd = code->JumpForward();
    code->Instructions()->SetItem(
      elfiConditionEnd - 1, Object::CreatePopJumpIfFalse(static_cast<int64_t>(
                              elifBlockEnd - elfiConditionEnd + 1
                            ))
    );
    elifBlockEnds.Push(elifBlockEnd);
  }

  // 处理 else 块
  if (elseStmts->Length() > 0) {
    // 生成 else 块的字节码
    Object::ForEach(elseStmts, [&codeList](const Object::PyObjPtr& stmt) {
      stmt->as<Ast::INode>()->emit(codeList);
    });
  }

  // 计算 then 块中 JUMP_FORWARD 的实际跳转偏移量
  Index ifEnd = code->Instructions()->Length();
  for (Index i = 0; i < elifBlockEnds.Size(); ++i) {
    code->Instructions()->SetItem(
      elifBlockEnds[i] - 1,
      Object::CreateJumpForward(ifEnd - elifBlockEnds[i] + 1)
    );
  }

  code->Instructions()->SetItem(
    thenBlockEnd - 1, Object::CreateJumpForward(ifEnd - thenBlockEnd + 1)
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
