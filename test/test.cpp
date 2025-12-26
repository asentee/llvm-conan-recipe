#include <iostream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#ifdef LLVM_PROJECT_CLANG_ENABLED
    #include <clang-c/Index.h>
#endif // LLVM_PROJECT_CLANG_ENABLED

int main() {
    llvm::LLVMContext context;

    std::unique_ptr<llvm::Module> module =
        std::make_unique<llvm::Module>("test_module", context);

    llvm::outs() << "LLVM Installation Check:\n";
    module->print(llvm::outs(), nullptr);

    #ifdef LLVM_PROJECT_CLANG_ENABLED
        // Test libclang
        std::cout << "Testing enabled LLVM project: Clang\n";
        auto index = clang_createIndex(0, 0);
        auto unit = clang_parseTranslationUnit(
            index,
            "test_package.cpp",
            nullptr,
            0,
            nullptr,
            0,
            CXTranslationUnit_None
        );

        if(unit == nullptr) {
            std::cerr << "Failed to parse translation unit. Quitting...\n";
            return -1;
        }
        auto cursor = clang_getTranslationUnitCursor(unit);
    #endif // LLVM_PROJECT_CLANG_ENABLED

    return 0;
}