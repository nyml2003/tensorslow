
// #include "Collections/Matrix.h"
// #include <stdexcept>
// #include "Collections/impl/String.h"

// namespace torchlight::Collections {

// Matrix::Matrix(Index rows, Index cols)
//   : rows(rows), cols(cols), data(rows * cols) {
//   data.Fill(0);
// }

// Matrix::Matrix(Index rows, Index cols, List<double> data)
//   : rows(rows), cols(cols), data(std::move(data)) {}

// String Matrix::ToString() const {
//   String str;
//   str.InplaceConcat(CreateStringWithCString("["));
//   for (Index i = 0; i < rows; i++) {
//     str.InplaceConcat(CreateStringWithCString("["));
//     for (Index j = 0; j < cols; j++) {
//       str.InplaceConcat(Collections::ToString(At(i, j)));
//       if (j != cols - 1) {
//         str.InplaceConcat(CreateStringWithCString(","));
//       }
//     }
//     str.InplaceConcat(CreateStringWithCString("]"));
//   }
//   str.InplaceConcat(CreateStringWithCString("]"));
//   return str;
// }

// Matrix Matrix::Transpose() const {
//   Matrix result(cols, rows);
//   for (Index i = 0; i < rows; i++) {
//     for (Index j = 0; j < cols; j++) {
//       result.data.Set(j * rows + i, At(i, j));
//     }
//   }
//   return result;
// }
// /**
//  * @brief
//  * @details
// 维度匹配：两个数组在进行操作时，它们的形状必须在所有维度上兼容。这意味着两个数组的形状在每个维度上要么相同，要么其中一个数组在该维度上的大小为1。

// 大小为1的维度：如果两个数组的形状在某个维度上不匹配，那么其中一个数组在该维度上的大小必须是1。这样，才能将该数组沿着该维度“广播”到匹配另一个数组的形状。

// 没有负数或零维度：不允许负数或零维度的数组进行广播。

// 没有维度上的重叠：如果两个数组在某个维度上的大小都大于1，那么它们在这个维度上的大小必须相同。

// 没有形状为(0,)的数组：不允许形状为(0,)的数组参与广播，因为它们没有有效的广播规则。

// 没有形状为(1,)和(0,)的数组组合：如果一个数组的形状为(1,)，另一个数组的形状为(0,)，不允许它们进行广播。

// 没有形状为(0,)和(0,)的数组组合：两个形状都为(0,)的数组不能进行广播，因为它们没有有效的广播规则。

// 没有形状为(0,)的数组与非(1,)形状的数组组合：一个形状为(0,)的数组不能与另一个在任何维度上大小不为1的数组进行广播。

// 没有形状为(1,)的数组与形状为(0,)的数组组合：一个形状为(1,)的数组不能与另一个形状为(0,)的数组进行广播。
//  * @param other
//  * @return 4位二进制数，从右到左依次表示：
//  *         - 第1位：other是否可以在列上广播到this
//  *         - 第2位：other是否可以在行上广播到this
//  *         - 第3位：this是否可以在列上广播到other
//  *         - 第4位：this是否可以在行上广播到other
//  */
// uint8_t Matrix::CheckBroadcast(const Matrix& other) const {
//   if (rows == other.rows && cols == other.cols) {
//     return 0b1111;
//   }
//   uint8_t result = 0b0000;

//   // 检查this是否可以在列上广播到other
//   if (cols == 1 && other.cols != 1) {
//     result |= 0b1000;  // 设置第4位
//   }
//   if (rows == 1 && other.rows != 1) {
//     result |= 0b0100;  // 设置第3位
//   }

//   // 检查other是否可以在列上广播到this
//   if (other.cols == 1 && cols != 1) {
//     result |= 0b0010;  // 设置第2位
//   }
//   if (other.rows == 1 && rows != 1) {
//     result |= 0b0001;  // 设置第1位
//   }
//   return result;
// }

// double Matrix::BroadcastAt(Index row, Index col, uint8_t broadcast_type)
// const {
//   if (broadcast_type & 0b10 && broadcast_type & 0b01) {
//     return At(0, 0);
//   }
//   if (broadcast_type & 0b01) {
//     return At(0, col);
//   }
//   if (broadcast_type & 0b10) {
//     return At(row, 0);
//   }
//   return At(row, col);
// }

// Matrix Matrix::Add(const Matrix& other) const {
//   uint8_t broadcast_type = CheckBroadcast(other);
//   if (broadcast_type == 0) {
//     throw std::invalid_argument("Matrix::Add: Matrix dimensions must be
//     equal");
//   }
//   if (broadcast_type == 0b1111) {
//     Matrix result(rows, cols);
//     for (Index i = 0; i < rows; i++) {
//       for (Index j = 0; j < cols; j++) {
//         result.data.Set(i * cols + j, At(i, j) + other.At(i, j));
//       }
//     }
//     return result;
//   }
//   Matrix result(std::max(rows, other.rows), std::max(cols, other.cols));
//   for (Index i = 0; i < result.rows; i++) {
//     for (Index j = 0; j < result.cols; j++) {
//       result.data.Set(
//         i * result.cols + j, BroadcastAt(i, j, (broadcast_type & 0b1100) >>
//         2) +
//                                other.BroadcastAt(i, j, broadcast_type &
//                                0b0011)
//       );
//     }
//   }
//   return result;
// }

// Matrix Matrix::Multiply(const Matrix& other) const {
//   uint8_t broadcast_type = CheckBroadcast(other);
//   if (broadcast_type == 0) {
//     throw std::invalid_argument("Matrix dimensions must be equal");
//   }

//   if (broadcast_type == 0b1111) {
//     Matrix result(rows, cols);
//     for (Index i = 0; i < rows; i++) {
//       for (Index j = 0; j < cols; j++) {
//         result.data.Set(i * cols + j, At(i, j) * other.At(i, j));
//       }
//     }
//     return result;
//   }
//   Matrix result(std::max(rows, other.rows), std::max(cols, other.cols));
//   for (Index i = 0; i < result.rows; i++) {
//     for (Index j = 0; j < result.cols; j++) {
//       result.data.Set(
//         i * result.cols + j, BroadcastAt(i, j, (broadcast_type & 0b1100) >>
//         2) *
//                                other.BroadcastAt(i, j, broadcast_type &
//                                0b0011)
//       );
//     }
//   }
//   return result;
// }

// Matrix Matrix::Multiply(double scalar) const {
//   Matrix result(rows, cols);
//   for (Index i = 0; i < rows; i++) {
//     for (Index j = 0; j < cols; j++) {
//       result.data.Set(i * cols + j, At(i, j) * scalar);
//     }
//   }
//   return result;
// }

// Index Matrix::Rows() const {
//   return rows;
// }

// Index Matrix::Cols() const {
//   return cols;
// }

// List<double> Matrix::Data() const {
//   return data;
// }

// double Matrix::At(Index row, Index col) const {
//   return data.Get(row * cols + col);
// }

// Matrix Matrix::InplaceReshape(Index rows, Index cols) const {
//   if (rows * cols != this->rows * this->cols) {
//     throw std::invalid_argument("Matrix dimensions must be equal");
//   }
//   return {rows, cols, data};
// }

// Matrix Matrix::MatrixMultiply(const Matrix& other) const {
//   Matrix result(rows, other.cols);
//   for (Index i = 0; i < rows; i++) {
//     for (Index j = 0; j < other.cols; j++) {
//       double sum = 0;
//       for (Index k = 0; k < cols; k++) {
//         sum += At(i, k) * other.At(k, j);
//       }
//       result.data.Set(i * other.cols + j, sum);
//     }
//   }
//   return result;
// }

// Matrix Matrix::eye(Index n) {
//   Matrix result(n, n);
//   for (Index i = 0; i < n; i++) {
//     result.data.Set(i * n + i, 1);
//   }
//   return result;
// }
// }  // namespace torchlight::Collections
