// #ifndef TORCHLIGHT_MATRIX_H
// #define TORCHLIGHT_MATRIX_H

// #include "Collections/List.h"
// #include "Collections/String.h"
// namespace torchlight::Collections {
// class Matrix {
//  private:
//   Index rows{};
//   Index cols{};
//   List<double> data;

//   [[nodiscard]] uint8_t CheckBroadcast(const Matrix& other) const;

//   [[nodiscard]] double BroadcastAt(Index row, Index col, uint8_t
//   broadcast_type)
//     const;

//  public:
//   [[nodiscard]] String ToString() const;
//   Matrix(Index rows, Index cols);
//   Matrix(Index rows, Index cols, List<double> data);

//   [[nodiscard]] Matrix Transpose() const;

//   [[nodiscard]] Matrix Add(const Matrix& other) const;
//   [[nodiscard]] Matrix Multiply(const Matrix& other) const;
//   [[nodiscard]] Matrix Multiply(double scalar) const;

//   [[nodiscard]] Index Rows() const;
//   [[nodiscard]] Index Cols() const;
//   [[nodiscard]] List<double> Data() const;
//   [[nodiscard]] double At(Index row, Index col) const;
//   [[nodiscard]] Matrix InplaceReshape(Index rows, Index cols) const;

//   [[nodiscard]] Matrix MatrixMultiply(const Matrix& other) const;

//   static Matrix eye(Index n);
// };

// }  // namespace torchlight::Collections
// #endif