#ifndef ABSTRACT_SEARCHER_H
#define ABSTRACT_SEARCHER_H

#include "AbstractSearchable.h"
#include <vector>

class AbstractSearcher {
public:
    virtual ~AbstractSearcher() {}

    virtual std::vector<Position> search(const AbstractSearchable& searchable) = 0;
};

#endif // ABSTRACT_SEARCHER_H

