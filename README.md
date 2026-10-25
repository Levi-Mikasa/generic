# Generic

A generic data structure library written in C.

Generic is a personal open-source project that provides reusable data structure tools. The project focuses on clear interfaces, simple resource management, and a layered design.

The library is still under development. Features and interfaces may change as the project grows.

**Generic 是一个使用 C 语言编写的通用数据结构库。** 项目目前处于持续开发阶段，目标是提供可复用的数据结构基础能力，并通过分层设计让不同功能更容易维护和扩展。

## Features

### Current Features

- **Dynamic Array** — Basic dynamic array operations.
- **Stack and Queue** — Basic operations built on the array structure.
- **Binary Tree** — Basic binary tree construction and operations.
- **Tree Traversal** — Preorder, inorder, postorder, and level-order addressing.
- **Tree Data Access** — Read and modify data by traversal order.
- **Tree Deletion** — Delete a subtree by path or traversal order, with a callback for data cleanup.

当前已实现的功能以基础操作为主。具体接口及使用方式请参考项目头文件和测试代码。

## Design

Generic uses a layered design to separate basic structure construction from higher-level data structure operations.

- **Layer 1: Basic Construction**
  Provides basic operations for constructing and managing data structures.
- **Layer 2: Data Structures and Rules**
  Implements operations and rules based on the basic structures.
- **Layer 3: Composite Structures**
  Combines existing structures to implement more complex features.

This design is intended to make the library easier to maintain and extend.

项目采用分层设计，将基础结构构建、数据结构规则和组合功能分开。随着开发推进，各层的具体职责和接口可能继续调整。

## Binary Tree

The current binary tree APIs support:

- Inserting nodes to build a complete binary tree.
- Reading data by traversal order.
- Modifying node data by traversal order.
- Deleting a subtree by path.
- Deleting a subtree by traversal order.
- Releasing node data through a user-provided callback.

Example:

```
// Insert data into a complete binary tree.
TreeCompleteInsert(head, data);

// Read data using preorder addressing.
void *data = TreeDataRead(head, 0, TREE_PREORDER);

// Modify data using preorder addressing.
TreeDataWrite(head, 0, TREE_PREORDER, new_data);

// Delete a subtree and release its data.
TreeDataDelAPIbyOrder(head, TREE_PREORDER, 1, free);
```

**Note:** The example assumes that the required headers are included and `head` has been initialized correctly. Traversal indices follow the convention implemented by the library.

数据销毁回调由调用者提供。使用 `free` 时，必须确保对应数据可以独立释放，避免共享数据导致重复释放。

## Testing

Basic tests have been run for:

- Complete binary tree insertion.
- Preorder, inorder, postorder, and level-order data reading.
- Data modification.
- Subtree deletion by traversal order.
- Subtree deletion by path.

These tests verify the basic behavior of the current APIs. More boundary tests and memory checks are still needed.

目前已完成基础功能测试，但这不代表所有异常输入、内存安全和边界情况都已经得到全面验证。

## Build

The project is written in C.

Build instructions depend on the current project structure and build configuration. Please refer to the source files and build configuration included in this repository.

## Roadmap

Planned improvements may include:

- More complete boundary and memory tests.
- Additional data structures and operations.
- Improvements to API consistency and resource management.
- Better documentation and usage examples.

The roadmap may change as development continues.

## Contributing

Suggestions, bug reports, and discussions are welcome.

If you find a problem or have an idea for improvement, feel free to open an issue or submit a pull request.

欢迎提出问题、改进建议或参与代码协作。项目仍在持续开发中，合理的反馈有助于改进设计与实现。

## License

See the `LICENSE` file for license terms.

Please check the license before using, modifying, or redistributing this project.