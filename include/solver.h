#ifndef _SOLVER_H
#define _SOLVER_H

#include "ioutils.h"

#include <cassert>

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define DEFAULT_CLAUSE_SIZE 3

enum TriBool
{
    FALSE = 0,
    TRUE,
    UNASSIGNED
};

typedef uint32_t idx_type;

template <typename _Boolean>
class valuation : public std::vector<_Boolean>
{
    typedef std::vector<_Boolean> Base;
public:
    typedef _Boolean Boolean;

    typename Base::reference operator[](typename Base::size_type pos)
    {
        return Base::operator[](pos-1);
    }

    typename Base::const_reference operator[](typename Base::size_type pos) const
    {
        return Base::operator[](pos-1);
    }

    typename Base::reference at(typename Base::size_type pos)
    {
        return Base::operator[](pos-1);
    }

    template <typename T>
    friend std::ostream& operator<< (std::ostream&, const valuation<T>&);
};

template <typename T>
std::ostream& operator<< (std::ostream& ostr, const valuation<T>& val)
{
    for (int32_t idx = 1; idx <= val.size(); ++idx)
    {
        ostr << (val[idx] ? idx : -idx) << " ";
    }
    return ostr;
}

template <typename Literal=int16_t>
class _clause
{
    public:
    typedef Literal literal_type;
    typedef typename std::vector<literal_type>::iterator iterator;

    _clause(const idx_type size = DEFAULT_CLAUSE_SIZE) :
        positive(0), resolved(0), decision_level(0),  data()
    {
        data.reserve(size);
    }
    void addVariable(const literal_type var)
    {
        data.push_back(var);
    }

    void createClause(std::vector<literal_type>&& _data) {
        data = _data;
    }

    inline bool isSatisfied() const {
        return positive > 0;
    }

    inline bool isUnitClause() const {
        return ((data.size() - resolved) == 1) && !isSatisfied();
    }

    bool isEmpty() const {
        return (resolved == data.size()) && !isSatisfied();
    }

    void done() {
        auto end = std::unique(data.begin(), data.end());
        data.erase(end, data.end());
        data.shrink_to_fit();
    }

    iterator begin() {
        return data.begin();
    }

    iterator end() {
        return begin() + (data.size() - resolved);
    }

    bool removeLiteral(const literal_type l) {
        auto it = find(begin(), end(), l);

        if (it == end()) return false;
        std::swap(it[0], data.end()[-1]);
        ++resolved;
        return true;
    }

    bool addSatisfyingLiteral(const literal_type l) {
        bool becameSatisfied = !positive;
        if (!removeLiteral(l)) return false;
        ++positive;
        return becameSatisfied;
    }

    uint8_t positive;
    uint8_t resolved;
    uint16_t decision_level;
    std::vector<literal_type> data;
};

typedef _clause<int16_t> clause;

template <typename ClauseType, typename ValuationType>
class computation_context
{
    public:
    typedef ClauseType clause_type;
    typedef typename clause::literal_type literal_type;

    typedef ValuationType valuation_type;
    typedef typename valuation_type::Boolean Boolean;

    computation_context() :
        numVars(0),
        numClauses(0),
        positive_occur(),
        negative_occur()
#ifdef REMOVE_PURE_LITERAL
        removed_positive_occur(),
        removed_negative_occur()
#endif
    {
    }

    void initialise()
    {
        valuation.resize(numVars);
        for (auto& v : valuation) v = UNASSIGNED;
    }

    void setValuation(const literal_type lit, const Boolean b)
    {
        valuation[lit] = b;
        // DO SOME STUFF
        // like remove occurences and so on
    }

    literal_type numVars;
    uint32_t numClauses;
    std::vector<std::vector<idx_type>> positive_occur;
    std::vector<std::vector<idx_type>> negative_occur;
    valuation_type valuation;

#ifdef REMOVE_PURE_LITERAL
    std::vector<std::vector<idx_type>> removed_positive_occur;
    std::vector<std::vector<idx_type>> removed_negative_occur;
#endif
};

enum Result
{
    UNSATISFIED = 0,
    SATISFIED,
    UNKNOWN,
};

template <typename IO, typename ClauseType, typename ValuationType, typename LiteralFeeder>
class solver
{
    typedef typename ClauseType::literal_type literal_type;
    public:
    solver(IO& _io) :
        ctx(),
        feeder(ctx),
        io(_io),
        formula(),
        restartsCounter(0)
    {
    }

    void fillFormula() {
        io.read(ctx, formula);
    }

    void run() {
        Result res = solve();
    }

    void restart() {
#ifdef VERBOSE
        io.printComment("restaring");
#endif
        ++restartsCounter;
    }

    void preprocess() {

    }

    Result solve() {
        if (find_if(formula.begin(), formula.end(), [](const ClauseType& cl) { return cl.isEmpty(); }) != formula.end())
        {
#ifdef VERBOSE
            io.printComment("Has found conflict");
#endif
           return UNSATISFIED;
        }
        unitPropagate();

#ifdef REMOVE_PURE_LITERAL
        for (const auto& l : ctx.unasignedLiterals)
        {
            if (ctx.positive_occur[l].size() == 0); // x_l does not occure in any literal => assign False
            else if (ctx.negative_occur[l].size() == 0); // ~x_l does not occure in any literal => assign True
        }
#endif
        literal_type literal = feeder.getLiteral();
        if (literal == 0) return SATISFIED;

        TriBool val = feeder.getValuation(literal);
        ctx.setValuation(literal, val);

        if (solve() == SATISFIED)
            return SATISFIED;

        ctx.setValuation(literal, (val ? FALSE : TRUE));
        return solve();
    }

    void unitPropagate(){}

    computation_context<ClauseType, ValuationType> ctx;
    LiteralFeeder feeder;
    IO& io;
    std::vector<ClauseType> formula;
    uint16_t restartsCounter;
};

#endif // _SOLVER_H
