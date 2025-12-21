#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/SourceMgr.h>

#ifdef TEST_LIB_CLANG_FOUND
    #include <clang-c/Index.h>
#endif

#include <iostream>
#include <memory>


int main(int argc, char const* argv[]) {
    if (argc < 2)
        return 0;

    llvm::InitializeNativeTarget();
    llvm::SMDiagnostic smd;
    llvm::LLVMContext context;
    std::string error;

    llvm::EngineBuilder engine_builder{
        llvm::parseIRFile(argv[1], smd, context)
    };
    engine_builder.setEngineKind(llvm::EngineKind::Interpreter);
    engine_builder.setErrorStr(&error);

    auto execution_engine = std::unique_ptr<llvm::ExecutionEngine>(
        engine_builder.create()
    );
    execution_engine->runStaticConstructorsDestructors(false);

    auto test_function = execution_engine->FindFunctionNamed("test");
    auto result = execution_engine->runFunction(
        test_function,
        llvm::ArrayRef<llvm::GenericValue>()
    );

    #ifdef TEST_LIB_CLANG_FOUND
        // Test libclang
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
    #endif

    return result.IntVal.getSExtValue();
}
