#ifndef Frontage_H
#define Frontage_H

#include "Parser.hpp"
#include "Scanner.hpp"
#include "Type.hpp"

#include <cstdint>
#include <list>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace spl {
    struct ParseNode;
    using token_type = Parser::token_type;
    using variant_type = std::variant<int32_t, float, std::string>;

    class Frontage {

    public:
        std::vector<std::string> SysIncludePath;

        std::optional<std::string> findHeaderSys(const std::string &headerName);

        std::optional<std::string> findHeaderUser(const std::string &headerName, const std::string filePath);

        std::list<DefTable> m_defTableStack;
        std::list<VarTable> m_varTableStack;

        Frontage(std::string const &filePath);

        bool parse();

        void clear();

        std::string str() const;

        spl::location location() const;

        std::string error() const;

        void appendError(std::string const &error);

    private:
        std::list<std::unique_ptr<Frontage>> m_includeTree;
        Scanner m_scanner;
        Parser m_parser;
        std::list<std::unique_ptr<ParseNode>> m_ast;
        std::list<std::string> m_errors;
        spl::location m_location;

        bool sysFirstInclude(const std::string &name);

        bool userFirstInclude(const std::string &name);

        void increaseLine(int32_t line = 1);

        friend class Parser;

        friend class Scanner;
    };

    class SubFrontage : public Frontage {
    public:
        SubFrontage(std::string const &filePath);

        friend class Parser;

        friend class Scanner;
    };
}  // namespace spl

#endif  // Frontage_H
