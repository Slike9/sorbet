#include "verifier.h"
#include "ast/treemap/treemap.h"

namespace ruby_typer {
namespace ast {

class VerifierWalker {
public:
    Expression *preTransformExpression(core::Context ctx, Expression *original) {
        if (!isa_tree<EmptyTree>(original)) {
            ENFORCE(!original->loc.is_none(), "location is unset");
        }

        original->_sanityCheck();

        return original;
    }
};

std::unique_ptr<Expression> Verifier::run(core::Context ctx, std::unique_ptr<Expression> node) {
    if (!debug_mode) {
        return node;
    }
    VerifierWalker vw;
    return TreeMap<VerifierWalker>::apply(ctx, vw, move(node));
}

} // namespace ast
} // namespace ruby_typer
