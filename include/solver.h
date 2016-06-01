#ifndef _SOLVER_H
#define _SOLVER_H

#include "ioutils.h"

#include <cassert>

#include <vector>
#include <queue>

#define DEFAULT_CLAUSE_SIZE 3

typedef int32_t idx_type;

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

    void createClause(vector<literal_type>&& _data) {
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
        swap(it[0], data.end()[-1]);
        ++resolved;
        return true;
    }

    void addSatisfyingLiteral(const literal_type l) {
        if (!removeLiteral(l))
            return;
        ++positive;
    }

    uint8_t positive;
    uint8_t resolved;
    uint16_t decision_level;
    vector<literal_type> data;
};

typedef _clause<int16_t> clause;

template <typename IO, typename ClauseType, typename ValuationType, typename VariableFeeder>
class solver
{
    public:
        typedef typename ClauseType::literal_type literal_type;

        solver(IO& _io) :
            io(_io),
            numVars(),
            numClauses(),
            formula(),
            positive_occur(),
            negative_occur()
    {

    }

        void run() {
            io.read(formula);
        }

        void preprocess() {

        }

        void restart() {

        }

        int32_t numVars;
        int32_t numClauses;

        IO& io;
        vector<ClauseType> formula;
        vector<vector<idx_type>> positive_occur;
        vector<vector<idx_type>> negative_occur;
};

#endif // _SOLVER_H
