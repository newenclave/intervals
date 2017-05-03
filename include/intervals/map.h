#ifndef ETOOL_INTERVALS_MAP_H
#define ETOOL_INTERVALS_MAP_H

#include "intervals/tree.h"
#include "intervals/traits/std_map.h"
#include "intervals/traits/array_map.h"

#ifdef INTERVALS_TOP_NANESPACE
namespace INTERVALS_TOP_NANESPACE {
#endif

namespace intervals {

    template <typename KeyT, typename ValueT, typename Comp = std::less<KeyT>,
              typename AllocT = std::allocator<std::pair<const KeyT, ValueT> > >
    class map: public tree<traits::std_map<KeyT, ValueT, Comp, AllocT> > {

        using parent_type = tree< traits::std_map<KeyT, ValueT,Comp, AllocT> >;

    public:

        using domain_type       = KeyT;
        using mapped_type       = ValueT;
        using key_type          = typename parent_type::key_type;
        using value_type        = typename parent_type::value_type;
        using iterator          = typename parent_type::iterator;
        using const_iterator    = typename parent_type::const_iterator;
        using iterator_access   = typename parent_type::iterator_access;

        iterator insert( value_type val )
        {
            return parent_type::insert_impl(std::move(val));
        }

        template <typename IterT>
        void insert( IterT begin, IterT end )
        {
            for( ; begin != end; ++begin ) {
                insert( *begin );
            }
        }

        template <typename IterT>
        void merge( IterT begin, IterT end )
        {
            for( ; begin != end; ++begin ) {
                merge( *begin );
            }
        }

        iterator merge( value_type val )
        {
            return parent_type::merge_impl( std::move(val) );
        }

        template <typename IterT>
        void absorb( IterT begin, IterT end )
        {
            for( ; begin != end; ++begin ) {
                absorb( *begin );
            }
        }

        iterator absorb( value_type val )
        {
            return parent_type::absorb_impl( std::move(val) );
        }

        template <typename IterT>
        void cut( IterT begin, IterT end )
        {
            for( ; begin != end; ++begin ) {
                cut( *begin );
            }
        }

        iterator cut( const key_type &val )
        {
            return parent_type::cut_impl( val );
        }

        mapped_type &operator [ ] ( const key_type &k )
        {
            using C = typename key_type::cmp;

            auto itr = parent_type::find( k );

            if( (itr != parent_type::end( )) && C::equal( k, itr->first ) ) {
                return itr->second;
            } else {
                auto res = insert( std::make_pair( k, mapped_type( ) ) );
                return res->second;
            }
        }

        mapped_type &operator [ ]( const domain_type &k )
        {
            return operator [ ]( key_type( k ) );
        }
    };
}

#ifdef INTERVALS_TOP_NANESPACE
}
#endif

#endif // MAP_H
