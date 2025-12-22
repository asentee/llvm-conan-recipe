#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

int main() {
    llvm::LLVMContext context;

    std::unique_ptr<llvm::Module> module =
        std::make_unique<llvm::Module>("test_module", context);

    llvm::outs() << "LLVM Installation Check:\n";
    module->print(llvm::outs(), nullptr);

    return 0;
}