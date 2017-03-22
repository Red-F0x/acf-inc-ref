//
// member_watch.h
//
//  Created on: 22.03.2017
//      Author: ho11owman
//

#ifndef MEMBER_WATCH_H_
#define MEMBER_WATCH_H_ 1

namespace ref {

template <typename Index>
class member_watch;

template <typename Bean, std::size_t tt_index>
class member_watch<ref::index<Bean, tt_index>>
{
public:
    using index_type = ref::index<Bean, tt_index>;
    using bean_type = typename index_type::bean_type;

private:
    std::reference_wrapper<bean_type> m_bean;

public:
    /// \todo add templated, shared, unique ...
    constexpr member_watch(bean_type& t_bean) : m_bean {t_bean} {}

    constexpr auto operator() () const -> decltype(auto)
    {
        return ref::invoke_read<index_type>(m_bean);
    }

    template <typename Type>
    constexpr void operator() (Type&& t_value)
    {
        return ref::invoke_write(m_bean, std::forward<Type>(t_value));
    }
};

}  // namespace ref



#endif /* MEMBER_WATCH_H_ */
