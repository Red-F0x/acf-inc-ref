//
// bean_stream.h
//
//  Created on: 16.03.2017
//      Author: ho11owman
//

#ifndef BEAN_STREAM_H_
#define BEAN_STREAM_H_ 1

#include <iostream>

#include "ref/bean_traits.h"

namespace ref {

template <typename Schema>
class basic_bean_ostream
{
public:
    using schema_type = Schema;
    using type = basic_bean_ostream<schema_type>;

private:

public:
    template <typename Bean>
    type& operator<<(const Bean& t_bean)
    {
        static_assert(ref::is_bean_v<Bean>, "");

        std::cout << ref::name_of<Bean>::value << ' ' << '{' << '\n';
        std::cout << '}' << '\n';

        return *this;
    }
};

template <typename Schema>
struct basic_bean_stream : public basic_bean_ostream<Schema>
{
};

class json_schema
{
};

using json_stream = basic_bean_stream<json_schema>;

}  // namespace ref



#endif /* BEAN_STREAM_H_ */
