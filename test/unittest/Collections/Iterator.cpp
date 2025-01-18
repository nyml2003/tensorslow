#include "../test_default.h"

#include "Collections.h"

using namespace torchlight::Collections;

TEST(Iterator, ForwardIteration) {
  List<int32_t> list = {1, 2, 3, 4, 5};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  for (int32_t i = 1; i <= 5; ++i) {
    ASSERT_FALSE(it.End());
    ASSERT_EQ(it.Get(), i);
    it.Next();
  }
  ASSERT_TRUE(it.End());
}

TEST(Iterator, ReverseIteration) {
  List<int32_t> list = {1, 2, 3, 4, 5};
  Iterator<int32_t> it = Iterator<int32_t>::RBegin(list);

  for (int32_t i = 5; i >= 1; --i) {
    ASSERT_FALSE(it.End());
    ASSERT_EQ(it.Get(), i);
    it.Next();
  }
  ASSERT_TRUE(it.End());
}

TEST(Iterator, EmptyList) {
  List<int32_t> list;
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  ASSERT_TRUE(it.End());
}

TEST(Iterator, SingleElementList) {
  List<int32_t> list = {1};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  ASSERT_FALSE(it.End());
  ASSERT_EQ(it.Get(), 1);
  it.Next();
  ASSERT_TRUE(it.End());
}

TEST(Iterator, BoundaryConditions) {
  List<int32_t> list = {1, 2, 3};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  // Move past the end
  it.Next();
  it.Next();
  it.Next();
  ASSERT_TRUE(it.End());

}

TEST(Iterator, IteratorCopy) {
  List<int32_t> list = {1, 2, 3, 4, 5};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);
  Iterator<int32_t> itCopy = it;

  ASSERT_FALSE(it.End());
  ASSERT_FALSE(itCopy.End());
  ASSERT_EQ(it.Get(), 1);
  ASSERT_EQ(itCopy.Get(), 1);

  it.Next();
  ASSERT_EQ(it.Get(), 2);
  ASSERT_EQ(itCopy.Get(), 1);

  itCopy.Next();
  ASSERT_EQ(it.Get(), 2);
  ASSERT_EQ(itCopy.Get(), 2);
}

TEST(Iterator, IteratorAssignment) {
  List<int32_t> list = {1, 2, 3, 4, 5};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);
  Iterator<int32_t> itCopy = it;

  ASSERT_FALSE(it.End());
  ASSERT_FALSE(itCopy.End());
  ASSERT_EQ(it.Get(), 1);
  ASSERT_EQ(itCopy.Get(), 1);

  it.Next();
  ASSERT_EQ(it.Get(), 2);
  ASSERT_EQ(itCopy.Get(), 1);

  itCopy.Next();
  ASSERT_EQ(it.Get(), 2);
  ASSERT_EQ(itCopy.Get(), 2);
}

TEST(Iterator, IteratorException) {
  List<int32_t> list = {1, 2, 3};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  ASSERT_NO_THROW(it.Get());
  ASSERT_NO_THROW(it.Next());
  ASSERT_NO_THROW(it.Get());
  ASSERT_NO_THROW(it.Next());
  ASSERT_NO_THROW(it.Get());
  ASSERT_NO_THROW(it.Next());
  ASSERT_THROW(it.Get(), std::out_of_range);
}

TEST(Iterator, IteratorEnd) {
  List<int32_t> list = {1, 2, 3};
  Iterator<int32_t> it = Iterator<int32_t>::Begin(list);

  while (!it.End()) {
    it.Next();
  }
  ASSERT_TRUE(it.End());
  ASSERT_THROW(it.Get(), std::out_of_range);
}