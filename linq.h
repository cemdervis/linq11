/*
   The MIT License (MIT)

   Copyright (c) 2015-2016 Cemalettin Dervis

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

namespace linq
{
    /**
     * Defines a direction for sorting ranges.
     */
    enum class sort_direction
    {
        /**
         * Sort elements in an ascending order.
         */
        ascending,
        
        /**
         * Sort elements in a descending order.
         */
        descending
    };

    namespace details
    {
        // ----------------------------------
        // Range declarations
        // ----------------------------------

        template<typename TPrevRange, typename TPredicate>
        class where_range;

        template<typename TPrevRange>
        class distinct_range;

        template<typename TPrevRange, typename TTransform>
        class select_range;

        template<typename TPrevRange, typename TTransform>
        class select_many_range;

        template<typename TPrevRange>
        class reverse_range;

        template<typename TPrevRange>
        class take_range;

        template<typename TPrevRange, typename TPredicate>
        class take_while_range;

        template<typename TPrevRange>
        class skip_range;

        template<typename TPrevRange, typename TPredicate>
        class skip_while_range;

        template<typename TPrevRange, typename TOtherRange>
        class append_range;

        template<typename TPrevRange>
        class repeat_range;

        template<
            typename TPrevRange, typename TOtherRange,
            typename TKeySelectorA, typename TKeySelectorB,
            typename TTransform
        >
        class join_range;

        template<typename TPrevRange, typename TKeySelector>
        class order_by_range;

        template<typename TPrevRange, typename TKeySelector>
        class then_by_range;

        // ----------------------------------
        // Average calculators
        // ----------------------------------

        // Calculates the average of a specific range.
        template<typename TRange, typename TInput>
        struct avg_calculator
        {
            using output_t = TInput;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();
                return (count > 0) ? (op.sum() / count) : output_t();
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, short>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, int>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, long>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, long long>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, unsigned short>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, unsigned int>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, unsigned long>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, unsigned long long>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();

                return (count > 0) ?
                    (static_cast<double>(op.sum()) / count) :
                    0.0;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, float>
        {
            using output_t = float;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();
                return (count > 0) ? op.sum() / count : 0.0f;
            }
        };

        template<typename TRange>
        struct avg_calculator<TRange, double>
        {
            using output_t = double;

            output_t calc(const TRange& op) const
            {
                size_t count = op.count();
                return (count > 0) ? op.sum() / count : 0.0;
            }
        };

        // ----------------------------------
        // base_range
        // ----------------------------------

        // Base class to identify ALL range types (for compile-time type checking).
        class base_range_ident
        {
            /* Nothing to define here. */
        };

        // Base class for sorting ranges (for compile-time type checking).
        class sorting_range
        {
            /* Nothing to define here. */
        };

        /**
        * Base class of all LINQ ranges.
        */
        template<
            typename TMy,       // The fully qualified type of this range.
            typename TOutput    // The full, unmodified type that is returned by this range.
        >
        class base_range : public base_range_ident
        {
        private:
            // Return non-const, non-volatile, non-reference types from methods such as sum, min and max.
            using output_t = typename std::decay<TOutput>::type;

        public:
            template<typename TPredicate>
            where_range<TMy, TPredicate> where(const TPredicate& predicate) const;

            distinct_range<TMy> distinct() const;

            template<typename TTransform>
            select_range<TMy, TTransform> select(const TTransform& transform) const;

            template<typename TTransform>
            select_many_range<TMy, TTransform> select_many(const TTransform& transform) const;

            reverse_range<TMy> reverse() const;

            take_range<TMy> take(size_t count) const;

            template<typename TPredicate>
            take_while_range<TMy, TPredicate> take_while(const TPredicate& predicate) const;

            skip_range<TMy> skip(size_t count) const;

            template<typename TPredicate>
            skip_while_range<TMy, TPredicate> skip_while(const TPredicate& predicate) const;

            template<typename TOtherRange>
            append_range<TMy, TOtherRange> append(const TOtherRange& otherRange) const;

            repeat_range<TMy> repeat(size_t count) const;

            template<typename TOtherRange, typename TKeySelectorA, typename TKeySelectorB, typename TTransform>
            join_range<TMy, TOtherRange, TKeySelectorA, TKeySelectorB, TTransform> join(
                const TOtherRange& otherRange,
                const TKeySelectorA& keySelectorA,
                const TKeySelectorB& keySelectorB,
                const TTransform& transform
                ) const;

            template<typename TKeySelector>
            order_by_range<TMy, TKeySelector> order_by(const TKeySelector& keySelector, sort_direction sortDir) const;

            template<typename TKeySelector>
            inline order_by_range<TMy, TKeySelector> order_by_ascending(const TKeySelector& keySelector) const
            {
                return order_by<TKeySelector>(keySelector, linq::sort_direction::ascending);
            }

            template<typename TKeySelector>
            inline order_by_range<TMy, TKeySelector> order_by_descending(const TKeySelector& keySelector) const
            {
                return order_by<TKeySelector>(keySelector, linq::sort_direction::descending);
            }

            template<typename TKeySelector>
            then_by_range<TMy, TKeySelector> then_by(const TKeySelector& keySelector, sort_direction sortDir) const;

            template<typename TKeySelector>
            inline then_by_range<TMy, TKeySelector> then_by_ascending(const TKeySelector& keySelector) const
            {
                return then_by<TKeySelector>(keySelector, linq::sort_direction::ascending);
            }

            template<typename TKeySelector>
            inline then_by_range<TMy, TKeySelector> then_by_descending(const TKeySelector& keySelector) const
            {
                return then_by<TKeySelector>(keySelector, linq::sort_direction::descending);
            }

            output_t sum() const;
            output_t min() const;
            output_t max() const;

            typename avg_calculator<TMy, output_t>::output_t average() const;

            template<typename TAccumFunc>
            output_t aggregate(const TAccumFunc& func) const;

            output_t first(const output_t& defaultValue = output_t()) const;

            template<typename TPredicate>
            output_t first(const TPredicate& predicate, const output_t& defaultValue = output_t()) const;

            output_t last(const output_t& defaultValue = output_t()) const;

            template<typename TPredicate>
            output_t last(const TPredicate& predicate, const output_t& defaultValue = output_t()) const;

            template<typename TPredicate>
            bool any(const TPredicate& predicate) const;

            template<typename TPredicate>
            bool all(const TPredicate& predicate) const;

            size_t count() const;

            template<typename TPredicate>
            size_t count(const TPredicate& predicate) const;

            output_t element_at(size_t index, const output_t& defaultValue = output_t()) const;

            std::vector<output_t> to_vector() const;
        };

        // ----------------------------------
        // where
        // ----------------------------------

        template<typename TPrevRange, typename TPredicate>
        class where_range : public base_range<
            where_range<TPrevRange, TPredicate>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(const where_range* parent, prev_iter_t begin, prev_iter_t end)
                    : Parent(parent)
                    , Begin(begin)
                    , End(end)
                {
                    const auto& pred = *Parent->Predicate;

                    // Seek the first match.
                    while (Begin != End && !pred(*Begin))
                    {
                        ++Begin;
                    }
                }

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                inline iterator& operator++()
                {
                    const auto& pred = *Parent->Predicate;

                    do
                    {
                        ++Begin;
                    } while (Begin != End && !pred(*Begin));

                    return *this;
                }

                inline output_t operator*() const { return *Begin; }

                const where_range* Parent;
                prev_iter_t Begin;
                prev_iter_t End;
            };

        public:
            where_range() = default;

            where_range(const TPrevRange& prev, const TPredicate& predicate)
                : Prev(prev)
                , Predicate(&predicate)
            {}

            inline iterator begin() const
            {
                return iterator(this, Prev.begin(), Prev.end());
            }

            inline iterator end() const
            {
                return iterator(this, Prev.end(), Prev.end());
            }

        private:
            TPrevRange Prev;
            const TPredicate* Predicate;
        };

        // ----------------------------------
        // distinct
        // ----------------------------------

        template<typename TPrevRange>
        class distinct_range : public base_range<
            distinct_range<TPrevRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        private:
            using prev_iter_t = typename TPrevRange::iterator;
            using object_container = std::vector<prev_iter_t>;

        public:
            struct iterator
            {
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(prev_iter_t begin, prev_iter_t end, object_container* encounteredObjects)
                    : Begin(begin)
                    , End(end)
                    , EncounteredObjects(encounteredObjects)
                {
                    if (Begin != End)
                    {
                        encounteredObjects->clear();
                        encounteredObjects->push_back(Begin);
                    }
                }

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                iterator& operator++()
                {
                    do
                    {
                        ++Begin;
                    } while (Begin != End && ContainsObject(Begin));

                    if (Begin != End)
                    {
                        EncounteredObjects->push_back(Begin);
                    }

                    return *this;
                }

                bool ContainsObject(const prev_iter_t& it)
                {
                    const auto& itVal = *it;

                    for (size_t i = 0; i < EncounteredObjects->size(); ++i)
                    {
                        if (*EncounteredObjects->at(i) == itVal)
                        {
                            return true;
                        }
                    }

                    return false;
                }

                inline output_t operator*() const { return *Begin; }

                prev_iter_t Begin;
                prev_iter_t End;
                object_container* EncounteredObjects;
            };

        public:
            distinct_range() = default;

            explicit distinct_range(const TPrevRange& prev)
                : Prev(prev)
            {}

            iterator begin() const
            {
                return iterator(Prev.begin(), Prev.end(), &EncounteredObjects);
            }

            iterator end() const
            {
                return iterator(Prev.end(), Prev.end(), &EncounteredObjects);
            }

        private:
            TPrevRange Prev;
            mutable object_container EncounteredObjects;
        };

        // ----------------------------------
        // select
        // ----------------------------------

        // Resolves the arguments that are passed to a select functor.
        template<typename TPrevRange>
        using select_transform_arg_t = typename std::add_const<
            typename std::add_lvalue_reference<typename TPrevRange::iterator::output_t>::type
        >::type;

        // Resolves the return type of a select functor.
        template<typename TPrevRange, typename TTransform>
        using select_output_t = typename std::result_of<
            TTransform(select_transform_arg_t<TPrevRange>)
        >::type;

        template<typename TPrevRange, typename TTransform>
        class select_range : public base_range<
            select_range<TPrevRange, TTransform>,
            select_output_t<TPrevRange, TTransform>
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = select_output_t<TPrevRange, TTransform>;

                iterator() = default;

                iterator(const select_range* parent, prev_iter_t begin, prev_iter_t end)
                    : Parent(parent)
                    , Begin(begin)
                    , End(end)
                {}

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                inline iterator& operator++()
                {
                    ++Begin;
                    return *this;
                }

                inline output_t operator*() const
                {
                    const auto& transform = *Parent->Transform;
                    return transform(*Begin);
                }

                const select_range* Parent;
                prev_iter_t Begin;
                prev_iter_t End;
            };

        public:
            select_range() = default;

            select_range(const TPrevRange& prev, const TTransform& transform)
                : Prev(prev)
                , Transform(&transform)
            {}

            inline iterator begin() const
            {
                return iterator(this, Prev.begin(), Prev.end());
            }

            inline iterator end() const
            {
                return iterator(this, Prev.end(), Prev.end());
            }

        private:
            TPrevRange Prev;
            const TTransform* Transform;
        };

        // ----------------------------------
        // select_many
        // ----------------------------------

        template<typename TPrevRange, typename TTransform>
        struct select_many_traits
        {
            using returned_range_t = typename std::result_of<
                TTransform(typename TPrevRange::iterator::output_t)
            >::type;

            // See if the returned type is really a range.
            static_assert(
                std::is_base_of<base_range_ident, returned_range_t>::value,
                "The transform function of select_many is expected to return a LINQ range."
                );

            using output_t = typename returned_range_t::iterator::output_t;
        };

        template<typename TPrevRange, typename TTransform>
        class select_many_range : public base_range<
            select_many_range<TPrevRange, TTransform>,
            typename select_many_traits<TPrevRange, TTransform>::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;

                using returned_range_t = typename select_many_traits<TPrevRange, TTransform>::returned_range_t;
                using returned_range_iter_t = typename returned_range_t::iterator;
                using output_t = typename returned_range_iter_t::output_t;

                iterator() = default;

                iterator(const select_many_range* parent, prev_iter_t pos, prev_iter_t end)
                    : Parent(parent)
                    , Pos(pos)
                    , End(end)
                {
                    if (Pos != End)
                    {
                        const auto& transform = *Parent->Transform;
                        bool first = true;

                        do
                        {
                            if (!first)
                            {
                                ++Pos;
                            }

                            if (Pos == End)
                            {
                                break;
                            }

                            RetRange = transform(*Pos);
                            RetBegin = RetRange.begin();
                            RetEnd = RetRange.end();

                            first = false;
                        }
                        while (RetBegin == RetEnd);
                    }
                }

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    if (RetBegin != RetEnd)
                    {
                        // There are values left to be obtained from the returned range.
                        ++RetBegin;
                    }

                    if (RetBegin == RetEnd)
                    {
                        // Move our parent iterator forward to get the next container.
                        ++Pos;
                        if (Pos != End)
                        {
                            const auto& transform = *Parent->Transform;
                            RetRange = transform(*Pos);
                            RetBegin = RetRange.begin();
                            RetEnd = RetRange.end();
                        }
                    }

                    return *this;
                }

                inline output_t operator*() const { return *RetBegin; }

                const select_many_range* Parent;
                prev_iter_t Pos;
                prev_iter_t End;

                returned_range_t RetRange;
                returned_range_iter_t RetBegin;
                returned_range_iter_t RetEnd;
            };

        public:
            select_many_range() = default;

            select_many_range(const TPrevRange& prev, const TTransform& transform)
                : Prev(prev)
                , Transform(&transform)
            {}

            inline iterator begin() const
            {
                return iterator(this, Prev.begin(), Prev.end());
            }

            inline iterator end() const
            {
                return iterator(this, Prev.end(), Prev.end());
            }

        private:
            TPrevRange Prev;
            const TTransform* Transform;
        };

        // ----------------------------------
        // reverse
        // ----------------------------------

        template<typename TPrevRange>
        class reverse_range : public base_range<
            reverse_range<TPrevRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        private:
            using prev_iter_t = typename TPrevRange::iterator;
            using object_container = std::vector<prev_iter_t>;

        public:
            struct iterator
            {
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(const object_container* prevIterators, size_t index)
                    : PrevIterators(prevIterators)
                    , Index(index)
                {}

                inline bool operator==(const iterator& o) const { return Index == o.Index; }
                inline bool operator!=(const iterator& o) const { return Index != o.Index; }

                inline iterator& operator++()
                {
                    --Index;
                    return *this;
                }

                inline output_t operator*() const { return *PrevIterators->at(Index); }

                const object_container* PrevIterators;
                size_t Index;
            };

        public:
            reverse_range() = default;

            explicit reverse_range(const TPrevRange& prev)
                : Prev(prev)
            {}

            inline iterator begin() const
            {
                PrevIterators.clear();
                for (auto beg = Prev.begin(), end = Prev.end(); beg != end; ++beg)
                {
                    PrevIterators.push_back(beg);
                }

                return iterator(&PrevIterators, PrevIterators.size() - 1);
            }

            inline iterator end() const
            {
                return iterator(nullptr, -1);
            }

        private:
            TPrevRange Prev;
            mutable object_container PrevIterators;
        };

        // ----------------------------------
        // take
        // ----------------------------------

        template<typename TPrevRange>
        class take_range : public base_range<
            take_range<TPrevRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(prev_iter_t begin, size_t count)
                    : Begin(begin)
                    , Count(count)
                {}

                inline bool operator==(const iterator& o) const { return Count == o.Count || Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Count != o.Count && Begin != o.Begin; }

                inline iterator& operator++()
                {
                    ++Begin;
                    --Count;
                    return *this;
                }

                inline output_t operator*() const { return *Begin; }

                prev_iter_t Begin;
                size_t Count;
            };

        public:
            take_range() = default;

            take_range(const TPrevRange& prev, size_t count)
                : Prev(prev)
                , Count(count)
            {}

            inline iterator begin() const
            {
                return iterator(Prev.begin(), Count);
            }

            inline iterator end() const
            {
                return iterator(Prev.end(), 0);
            }

        private:
            TPrevRange Prev;
            size_t Count;
        };

        // ----------------------------------
        // take_while
        // ----------------------------------

        template<typename TPrevRange, typename TPredicate>
        class take_while_range : public base_range<
            take_while_range<TPrevRange, TPredicate>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(const take_while_range* parent, prev_iter_t begin, prev_iter_t end)
                    : Parent(parent)
                    , Begin(begin)
                    , End(end)
                {
                    const auto& pred = *Parent->Predicate;
                    if (Begin != End && !pred(*Begin))
                    {
                        Begin = End;
                    }
                }

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                inline iterator& operator++()
                {
                    ++Begin;

                    const auto& pred = *Parent->Predicate;
                    if (Begin != End && !pred(*Begin))
                    {
                        Begin = End;
                    }

                    return *this;
                }

                inline output_t operator*() const { return *Begin; }

                const take_while_range* Parent;
                prev_iter_t Begin;
                prev_iter_t End;
            };

        public:
            take_while_range() = default;

            take_while_range(const TPrevRange& prev, const TPredicate& predicate)
                : Prev(prev)
                , Predicate(&predicate)
            {}

            inline iterator begin() const
            {
                return iterator(this, Prev.begin(), Prev.end());
            }

            inline iterator end() const
            {
                return iterator(this, Prev.end(), Prev.end());
            }

        private:
            TPrevRange Prev;
            const TPredicate* Predicate;
        };

        // ----------------------------------
        // skip
        // ----------------------------------

        template<typename TPrevRange>
        class skip_range : public base_range<
            skip_range<TPrevRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(prev_iter_t begin, prev_iter_t end, size_t count)
                    : Begin(begin)
                {
                    while (Begin != end && count > 0)
                    {
                        ++Begin;
                        --count;
                    }
                }

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                inline iterator& operator++()
                {
                    ++Begin;
                    return *this;
                }

                inline output_t operator*() const { return *Begin; }

                prev_iter_t Begin;
            };

        public:
            skip_range(const TPrevRange& prev, size_t count)
                : Prev(prev)
                , Count(count)
            {}

            inline iterator begin() const
            {
                return iterator(Prev.begin(), Prev.end(), Count);
            }

            inline iterator end() const
            {
                return iterator(Prev.end(), Prev.end(), 0);
            }

        private:
            TPrevRange Prev;
            size_t Count;
        };

        // ----------------------------------
        // skip_while
        // ----------------------------------

        template<typename TPrevRange, typename TPredicate>
        class skip_while_range : public base_range<
            skip_while_range<TPrevRange, TPredicate>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(prev_iter_t begin, prev_iter_t end, const TPredicate& predicate)
                    : Begin(begin)
                {
                    while (Begin != end && predicate(*Begin))
                    {
                        ++Begin;
                    }
                }

                inline bool operator==(const iterator& o) const { return Begin == o.Begin; }
                inline bool operator!=(const iterator& o) const { return Begin != o.Begin; }

                inline iterator& operator++()
                {
                    ++Begin;
                    return *this;
                }

                inline output_t operator*() const { return *Begin; }

                prev_iter_t Begin;
            };

        public:
            skip_while_range(const TPrevRange& prev, const TPredicate& predicate)
                : Prev(prev)
                , Predicate(&predicate)
            {}

            inline iterator begin() const
            {
                return iterator(Prev.begin(), Prev.end(), *Predicate);
            }

            inline iterator end() const
            {
                return iterator(Prev.end(), Prev.end(), *Predicate);
            }

        private:
            TPrevRange Prev;
            const TPredicate* Predicate;
        };

        // ----------------------------------
        // append
        // ----------------------------------

        template<typename TPrevRange, typename TOtherRange>
        class append_range : public base_range<
            append_range<TPrevRange, TOtherRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        private:
            using other_range_iter_t = typename TOtherRange::iterator;

        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(prev_iter_t begin, prev_iter_t end, other_range_iter_t otherBegin, other_range_iter_t otherEnd)
                    : MyBegin(begin)
                    , MyEnd(end)
                    , OtherBegin(otherBegin)
                    , OtherEnd(otherEnd)
                {}

                inline bool operator==(const iterator& o) const { return OtherBegin == o.OtherBegin; }
                inline bool operator!=(const iterator& o) const { return OtherBegin != o.OtherBegin; }

                inline iterator& operator++()
                {
                    if (MyBegin != MyEnd)
                    {
                        ++MyBegin;
                    }
                    else
                    {
                        ++OtherBegin;
                    }

                    return *this;
                }

                inline output_t operator*() const
                {
                    return (MyBegin != MyEnd) ? *MyBegin : *OtherBegin;
                }

                prev_iter_t MyBegin;
                prev_iter_t MyEnd;
                other_range_iter_t OtherBegin;
                other_range_iter_t OtherEnd;
            };

        public:
            append_range(const TPrevRange& prev, const TOtherRange& otherRange)
                : Prev(prev)
                , OtherRange(otherRange)
            {}

            inline iterator begin() const
            {
                return iterator(Prev.begin(), Prev.end(), OtherRange.begin(), OtherRange.end());
            }

            inline iterator end() const
            {
                return iterator(Prev.end(), Prev.end(), OtherRange.end(), OtherRange.end());
            }

        private:
            TPrevRange Prev;
            TOtherRange OtherRange;
        };

        // ----------------------------------
        // repeat
        // ----------------------------------

        template<typename TPrevRange>
        class repeat_range : public base_range<
            repeat_range<TPrevRange>,
            typename TPrevRange::iterator::output_t
        >
        {
        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = typename prev_iter_t::output_t;

                iterator() = default;

                iterator(TPrevRange* prevRangePtr, prev_iter_t begin, prev_iter_t end, size_t count)
                    : PrevRangePtr(prevRangePtr)
                    , Pos(begin)
                    , End(end)
                    , Count(count)
                {}

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    ++Pos;

                    if (Pos == End && Count > 0)
                    {
                        Pos = PrevRangePtr->begin();
                        --Count;
                    }

                    return *this;
                }

                inline output_t operator*() const
                {
                    return *Pos;
                }

                TPrevRange* PrevRangePtr;
                prev_iter_t Pos;
                prev_iter_t End;
                size_t Count;
            };

        public:
            repeat_range(const TPrevRange& prev, size_t count)
                : Prev(prev)
                , Count(count)
            {}

            inline iterator begin() const
            {
                return iterator(&Prev, Prev.begin(), Prev.end(), Count);
            }

            inline iterator end() const
            {
                return iterator(&Prev, Prev.end(), Prev.end(), 0);
            }

        private:
            mutable TPrevRange Prev;
            size_t Count;
        };

        // ----------------------------------
        // join
        // ----------------------------------

        // Determines the output of a selection in the join range.
        template<typename TRangeA, typename TRangeB, typename TTransform>
        using join_output_t = typename std::result_of<TTransform(
            typename TRangeA::iterator::output_t,
            typename TRangeB::iterator::output_t
            )>::type;

        // Nested loop inner join operator.
        template<
            typename TPrevRange, typename TOtherRange,
            typename TKeySelectorA, typename TKeySelectorB,
            typename TTransform
        >
        class join_range : public base_range<
            join_range<TPrevRange, TOtherRange, TKeySelectorA, TKeySelectorB, TTransform>,
            join_output_t<TPrevRange, TOtherRange, TTransform>
        >
        {
        private:
            using other_range_iter_t = typename TOtherRange::iterator;

        public:
            struct iterator
            {
                using prev_iter_t = typename TPrevRange::iterator;
                using output_t = join_output_t<TPrevRange, TOtherRange, TTransform>;

                iterator() = default;

                iterator(prev_iter_t begin, prev_iter_t end, const join_range* parent)
                    : Begin(begin)
                    , End(end)
                    , Pos(begin)
                    , OtherBegin(parent->OtherRange.begin())
                    , OtherEnd(parent->OtherRange.end())
                    , OtherPos(parent->OtherRange.begin())
                    , Parent(parent)
                {
                    // Find the first match without pre-incrementing the
                    // other position, so that we start at the beginning.
                    FindNext(false);
                }

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    // Find the next match, but pre-increment the other
                    // position, so that we can move forward.
                    FindNext(true);
                    return *this;
                }

                inline output_t operator*() const
                {
                    const auto& transform = *Parent->Transform;
                    return transform(*Pos, *OtherPos);
                }

                prev_iter_t Begin;
                prev_iter_t End;
                prev_iter_t Pos;

                other_range_iter_t OtherBegin;
                other_range_iter_t OtherEnd;
                other_range_iter_t OtherPos;

                const join_range* Parent;

            private:
                // Finds the next match in both ranges using the key selectors and == comparison.
                void FindNext(bool preIncrementOther)
                {
                    const auto& keySelectorA = *Parent->KeySelectorA;
                    const auto& keySelectorB = *Parent->KeySelectorB;

                    if (preIncrementOther)
                    {
                        ++OtherPos;
                    }

                    while (Pos != End)
                    {
                        bool shouldContinue = true;
                        const auto& keyA = keySelectorA(*Pos);

                        while (OtherPos != OtherEnd)
                        {
                            const auto& keyB = keySelectorB(*OtherPos);

                            if (keyA == keyB)
                            {
                                shouldContinue = false;
                                break;
                            }

                            ++OtherPos;
                        }

                        // Start over in the other range if it's finished.
                        if (OtherPos == OtherEnd)
                        {
                            OtherPos = OtherBegin;
                        }

                        if (!shouldContinue)
                        {
                            break;
                        }

                        ++Pos;
                    }
                }
            };

        public:
            join_range(
                const TPrevRange& prev,
                TOtherRange otherRange,
                const TKeySelectorA& keySelectorA,
                const TKeySelectorB& keySelectorB,
                const TTransform& transform)
                : Prev(prev)
                , OtherRange(otherRange)
                , KeySelectorA(&keySelectorA)
                , KeySelectorB(&keySelectorB)
                , Transform(&transform)
            {}

            inline iterator begin() const
            {
                return iterator(Prev.begin(), Prev.end(), this);
            }

            inline iterator end() const
            {
                return iterator(Prev.end(), Prev.end(), this);
            }

            TOtherRange OtherRange;
            const TKeySelectorA* KeySelectorA;
            const TKeySelectorB* KeySelectorB;
            const TTransform* Transform;

        private:
            TPrevRange Prev;
        };

        // ----------------------------------
        // order_by
        // ----------------------------------

        template<typename TPrevRange, typename TKeySelector>
        class order_by_range : public base_range<
            order_by_range<TPrevRange, TKeySelector>,
            typename TPrevRange::iterator::output_t
        >, public sorting_range
        {
        public:
            using container_element_t = typename std::decay<typename TPrevRange::iterator::output_t>::type;
            using container_t = std::vector<container_element_t>;
            using container_iter_t = typename container_t::const_iterator;

        public:
            struct iterator
            {
                using output_t = typename container_iter_t::reference;

                iterator() = default;

                iterator(container_iter_t pos)
                    : Pos(pos)
                {}

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    ++Pos;
                    return *this;
                }

                inline output_t operator*() const
                {
                    return *Pos;
                }

                container_iter_t Pos;
            };

            order_by_range(const TPrevRange& prev, const TKeySelector& keySelector, sort_direction sortDir)
                : Prev(prev)
                , KeySelector(&keySelector)
                , SortDirection(sortDir)
            {}

            inline iterator begin() const
            {
                SortedValues.clear();
                for (const auto& val : Prev)
                {
                    SortedValues.push_back(val);
                }
                
                std::sort(SortedValues.begin(), SortedValues.end(),
                    [this](const container_element_t& a, const container_element_t& b)
                {
                    return this->compare_keys(a, b);
                });

                return iterator(SortedValues.begin());
            }

            inline iterator end() const
            {
                return iterator(SortedValues.end());
            }

            inline bool compare_keys(const container_element_t& a, const container_element_t& b) const
            {
                const auto& keySelector = *KeySelector;
                const auto& aVal = keySelector(a);
                const auto& bVal = keySelector(b);

                if (SortDirection == sort_direction::ascending)
                {
                    return aVal < bVal;
                }
                else // descending
                {
                    return bVal < aVal;
                }
            }

        private:
            TPrevRange Prev;
            const TKeySelector* KeySelector;
            sort_direction SortDirection;
            mutable container_t SortedValues;
        };

        // ----------------------------------
        // then_by
        // ----------------------------------

        template<typename TPrevRange, typename TKeySelector>
        class then_by_range : public base_range<
            then_by_range<TPrevRange, TKeySelector>,
            typename TPrevRange::iterator::output_t
        >, public sorting_range
        {
            static_assert(std::is_assignable<sorting_range, TPrevRange>::value,
                "A then_by operation can only be appended to another then_by or order_by operation."
                );

        public:
            using container_element_t = typename std::decay<typename TPrevRange::iterator::output_t>::type;
            using container_t = std::vector<container_element_t>;
            using container_iter_t = typename container_t::const_iterator;

        public:
            struct iterator
            {
                using output_t = typename container_iter_t::reference;

                iterator() = default;

                iterator(container_iter_t pos)
                    : Pos(pos)
                {}

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    ++Pos;
                    return *this;
                }

                inline output_t operator*() const
                {
                    return *Pos;
                }

                container_iter_t Pos;
            };

            then_by_range(const TPrevRange& prev, const TKeySelector& keySelector, sort_direction sortDir)
                : Prev(prev)
                , KeySelector(&keySelector)
                , SortDirection(sortDir)
            {}

            inline iterator begin() const
            {
                SortedValues.clear();
                for (const auto& val : Prev)
                {
                    SortedValues.push_back(val);
                }

                std::sort(SortedValues.begin(), SortedValues.end(),
                    [this](const container_element_t& a, const container_element_t& b)
                {
                    return this->compare_keys(a, b);
                });

                return iterator(SortedValues.begin());
            }

            inline iterator end() const
            {
                return iterator(SortedValues.end());
            }

            inline bool compare_keys(const container_element_t& a, const container_element_t& b) const
            {
                const auto& keySelector = *KeySelector;
                const auto& aVal = keySelector(a);
                const auto& bVal = keySelector(b);

                if (Prev.compare_keys(a, b))
                {
                    return true;
                }
                else if (Prev.compare_keys(b, a))
                {
                    return false;
                }

                if (SortDirection == sort_direction::ascending)
                {
                    return aVal < bVal;
                }
                else // descending
                {
                    return bVal < aVal;
                }
            }

        private:
            TPrevRange Prev;
            const TKeySelector* KeySelector;
            sort_direction SortDirection;

            mutable container_t SortedValues;
        };

        // ----------------------------------
        // from_container
        // ----------------------------------

        template<typename T>
        struct add_const_to_reference
        {
            using type = T;
        };

        template<typename T>
        struct add_const_to_reference<T&>
        {
            using type = const T&;
        };

        template<typename TContainer>
        class from_container_parent_range
        {
        public:
            struct iterator
            {
                using output_t = typename TContainer::const_iterator::reference;
            };
        };

        template<typename TContainer>
        class from_container_range : public base_range<
            from_container_range<TContainer>,
            typename TContainer::const_iterator::value_type
        >
        {
        public:
            // Simply iterates through the container.
            struct iterator
            {
                using container_iter_t = typename TContainer::const_iterator;
                using output_t = typename from_container_parent_range<TContainer>::iterator::output_t;

                iterator() = default;

                iterator(container_iter_t pos)
                    : Pos(pos)
                {}

                inline bool operator==(const iterator& o) const { return Pos == o.Pos; }
                inline bool operator!=(const iterator& o) const { return Pos != o.Pos; }

                inline iterator& operator++()
                {
                    ++Pos;
                    return *this;
                }

                inline output_t operator*() const { return *Pos; }

                container_iter_t Pos;
            };

        public:
            from_container_range() = default;

            explicit from_container_range(const TContainer* vec)
                : Container(vec)
            {}

            inline iterator begin() const
            {
                return iterator(Container->begin());
            }

            inline iterator end() const
            {
                return iterator(Container->end());
            }

        private:
            const TContainer* Container;
        };

        // ----------------------------------
        // from_to_range
        // ----------------------------------

        template<typename T>
        class from_to_range : public base_range<from_to_range<T>, T>
        {
        public:
            struct iterator
            {
                using output_t = T;

                iterator() = default;

                iterator(const T& value, const T& bound, const T& step)
                    : Index(0)
                    , Start(value)
                    , Value(value)
                    , Bound(bound)
                    , Step(step)
                {}

                inline bool operator==(const iterator& o) const { return Value == o.Value; }
                inline bool operator!=(const iterator& o) const { return Value != o.Value; }

                inline iterator& operator++()
                {
                    ++Index;
                    return *this;
                }

                inline output_t operator*() const
                {
                    Value = (Step * Index) + Start;

                    if (Step < T())
                    {
                        if (Value < Bound)
                        {
                            Value = Bound;
                        }
                    }
                    else
                    {
                        if (Value > Bound)
                        {
                            Value = Bound;
                        }
                    }

                    return Value;
                }

                int Index;
                T Start;
                mutable T Value;
                T Bound;
                T Step;
            };

            from_to_range(const T& start, const T& end, const T& step)
                : Start(start)
                , End(end)
                , Step(step)
            {
                // Unsign the step value.
                if (Step < T())
                {
                    Step = -Step;
                }

                // Invert the step value if we're going backwards.
                if (Start > End)
                {
                    Step = -Step;
                }
            }

            inline iterator begin() const
            {
                return iterator(Start, End, Step);
            }

            inline iterator end() const
            {
                return iterator(End, T(), T());
            }

        private:
            T Start;
            T End;
            T Step;
        };

        // ----------------------------------
        // generate_range
        // ----------------------------------

        struct generator_return_value_ident
        {
            /* Nothing to define here. */
        };
        
        template<typename T>
        struct generator_return_value : public generator_return_value_ident
        {
            using value_type = T;
            
            generator_return_value()
                : IsEmpty(true)
            {}

            generator_return_value(const T& value)
                : Value(value)
                , IsEmpty(false)
            {}

            inline operator T&() { return Value; }
            inline operator const T&() const { return Value; }

            inline bool operator==(const generator_return_value& o) const
            {
                // We only care about whether two generator_return_values are empty or not.
                // If the iterator has an empty one, it will match the one from the last
                // iterator, which indicates the end of iteration.
                return IsEmpty == o.IsEmpty;
            }

            inline bool operator!=(const generator_return_value& o) const
            {
                // Same as in operator==.
                return IsEmpty != o.IsEmpty;
            }

            T Value;
            bool IsEmpty;
        };

        template<typename TGenerator>
        struct generate_range_traits
        {
            using generator_return_type = typename std::result_of<TGenerator(size_t)>::type;
            
            // Ensure that whatever the generator returned is indeed of type generator_return_type.
            static_assert(
                    std::is_base_of<generator_return_value_ident, generator_return_type>::value,
                    "The generator function is expected to return a result of linq::generate_return() or linq::generate_finish()."
                    );
            
            // The type that is wrapped by the returned generator_return_type.
            using core_type = typename generator_return_type::value_type;
        };
        
        template<typename TGenerator>
        class generate_range : public base_range<
            generate_range<TGenerator>,
            typename generate_range_traits<TGenerator>::core_type
        >
        {
        public:
            struct iterator
            {
                using generator_return_type = typename generate_range_traits<TGenerator>::generator_return_type;
                using output_t = typename generate_range_traits<TGenerator>::core_type;

                iterator() = default;

                iterator(const generate_range* parent, bool isEnd)
                    : Parent(parent)
                    , Iteration(0)
                {
                    if (isEnd)
                    {
                        LastResult = generator_return_type();
                    }
                    else
                    {
                        // First iteration.
                        const auto& generator = *Parent->Generator;
                        LastResult = generator(Iteration);
                    }
                }

                inline bool operator==(const iterator& o) const { return LastResult == o.LastResult; }
                inline bool operator!=(const iterator& o) const { return LastResult != o.LastResult; }

                inline iterator& operator++()
                {
                    ++Iteration;

                    const auto& generator = *Parent->Generator;
                    LastResult = generator(Iteration);
                    
                    return *this;
                }

                inline output_t operator*() const { return LastResult; }

                const generate_range* Parent;
                size_t Iteration;
                generator_return_type LastResult;
            };

            explicit generate_range(const TGenerator& generator)
                : Generator(&generator)
            {}

            inline iterator begin() const
            {
                return iterator(this, false);
            }

            inline iterator end() const
            {
                return iterator(this, true);
            }

        private:
            const TGenerator* Generator;
        };

        // ----------------------------------
        // base_range method definitions
        // ----------------------------------

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline where_range<TMy, TPredicate>
            base_range<TMy, TOutput>::where(const TPredicate& predicate) const
        {
            return where_range<TMy, TPredicate>(static_cast<const TMy&>(*this), predicate);
        }

        template<typename TMy, typename TOutput>
        inline distinct_range<TMy>
            base_range<TMy, TOutput>::distinct() const
        {
            return distinct_range<TMy>(static_cast<const TMy&>(*this));
        }

        template<typename TMy, typename TOutput>
        template<typename TTransform>
        inline select_range<TMy, TTransform>
            base_range<TMy, TOutput>::select(const TTransform & transform) const
        {
            return select_range<TMy, TTransform>(static_cast<const TMy&>(*this), transform);
        }

        template<typename TMy, typename TOutput >
        template<typename TTransform>
        inline select_many_range<TMy, TTransform>
            base_range<TMy, TOutput>::select_many(const TTransform & transform) const
        {
            return select_many_range<TMy, TTransform>(static_cast<const TMy&>(*this), transform);
        }

        template<typename TMy, typename TOutput>
        inline reverse_range<TMy>
            base_range<TMy, TOutput>::reverse() const
        {
            return reverse_range<TMy>(static_cast<const TMy&>(*this));
        }

        template<typename TMy, typename TOutput>
        inline take_range<TMy>
            base_range<TMy, TOutput>::take(size_t count) const
        {
            return take_range<TMy>(static_cast<const TMy&>(*this), count);
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline take_while_range<TMy, TPredicate>
            base_range<TMy, TOutput>::take_while(const TPredicate& predicate) const
        {
            return take_while_range<TMy, TPredicate>(static_cast<const TMy&>(*this), predicate);
        }

        template<typename TMy, typename TOutput>
        inline skip_range<TMy>
            base_range<TMy, TOutput>::skip(size_t count) const
        {
            return skip_range<TMy>(static_cast<const TMy&>(*this), count);
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline skip_while_range<TMy, TPredicate>
            base_range<TMy, TOutput>::skip_while(const TPredicate& predicate) const
        {
            return skip_while_range<TMy, TPredicate>(static_cast<const TMy&>(*this), predicate);
        }

        template<typename TMy, typename TOutput>
        template<typename TOtherRange>
        inline append_range<TMy, TOtherRange>
            base_range<TMy, TOutput>::append(const TOtherRange& otherRange) const
        {
            return append_range<TMy, TOtherRange>(static_cast<const TMy&>(*this), otherRange);
        }

        template<typename TMy, typename TOutput>
        inline repeat_range<TMy>
            base_range<TMy, TOutput>::repeat(size_t count) const
        {
            return repeat_range<TMy>(static_cast<const TMy&>(*this), count);
        }

        template<typename TMy, typename TOutput>
        template<typename TOtherRange, typename TKeySelectorA, typename TKeySelectorB, typename TTransform>
        inline join_range<TMy, TOtherRange, TKeySelectorA, TKeySelectorB, TTransform>
            base_range<TMy, TOutput>::join(
                const TOtherRange& otherRange,
                const TKeySelectorA& keySelectorA,
                const TKeySelectorB& keySelectorB,
                const TTransform& transform
                ) const
        {
            return join_range<TMy, TOtherRange, TKeySelectorA, TKeySelectorB, TTransform>(
                static_cast<const TMy&>(*this),
                otherRange,
                keySelectorA,
                keySelectorB,
                transform
                );
        }

        template<typename TMy, typename TOutput>
        template<typename TKeySelector>
        inline order_by_range<TMy, TKeySelector> base_range<TMy, TOutput>::order_by(
            const TKeySelector& keySelector,
            sort_direction sortDir
            ) const
        {
            return order_by_range<TMy, TKeySelector>(
                static_cast<const TMy&>(*this),
                keySelector,
                sortDir
                );
        }

        template<typename TMy, typename TOutput>
        template<typename TKeySelector>
        inline then_by_range<TMy, TKeySelector> base_range<TMy, TOutput>::then_by(
            const TKeySelector& keySelector,
            sort_direction sortDir
            ) const
        {
            return then_by_range<TMy, TKeySelector>(
                static_cast<const TMy&>(*this),
                keySelector,
                sortDir
                );
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::sum() const
        {
            bool first = true;
            output_t sum = output_t();

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (first)
                {
                    sum = p;
                    first = false;
                }
                else
                {
                    sum += p;
                }
            }

            return sum;
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::min() const
        {
            bool first = true;
            output_t min = output_t();

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (first)
                {
                    min = p;
                    first = false;
                }
                else if (p < min)
                {
                    min = p;
                }
            }

            return min;
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::max() const
        {
            bool first = true;
            output_t max = output_t();

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (first)
                {
                    max = p;
                    first = false;
                }
                else if (max < p)
                {
                    max = p;
                }
            }

            return max;
        }

        template<typename TMy, typename TOutput>
        inline typename avg_calculator<TMy, typename base_range<TMy, TOutput>::output_t>::output_t
            base_range<TMy, TOutput>::average() const
        {
            return avg_calculator<TMy, output_t>().calc(static_cast<const TMy&>(*this));
        }

        template<typename TMy, typename TOutput>
        template<typename TAccumFunc>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::aggregate(const TAccumFunc& func) const
        {
            bool first = true;
            output_t sum = output_t();

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (first)
                {
                    sum = p;
                    first = false;
                }
                else
                {
                    sum = func(sum, p);
                }
            }

            return sum;
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::first(const output_t& defaultValue) const
        {
            for (const auto& p : static_cast<const TMy&>(*this))
            {
                return p;
            }

            return defaultValue;
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::first(const TPredicate& predicate, const output_t& defaultValue) const
        {
            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (predicate(p))
                {
                    return p;
                }
            }

            return defaultValue;
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::last(const output_t& defaultValue) const
        {
            output_t ret = defaultValue;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                ret = p;
            }

            return ret;
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::last(const TPredicate& predicate, const output_t& defaultValue) const
        {
            output_t ret = defaultValue;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (predicate(p))
                {
                    ret = p;
                }
            }

            return ret;
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline bool base_range<TMy, TOutput>::any(const TPredicate& predicate) const
        {
            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (predicate(p))
                {
                    return true;
                }
            }

            return false;
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        inline bool base_range<TMy, TOutput>::all(const TPredicate& predicate) const
        {
            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (!predicate(p))
                {
                    return false;
                }
            }

            return true;
        }

        template<typename TMy, typename TOutput>
        size_t base_range<TMy, TOutput>::count() const
        {
            size_t ret = 0;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                ++ret;
            }

            return ret;
        }

        template<typename TMy, typename TOutput>
        template<typename TPredicate>
        size_t base_range<TMy, TOutput>::count(const TPredicate& predicate) const
        {
            size_t ret = 0;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (predicate(p))
                {
                    ++ret;
                }
            }

            return ret;
        }

        template<typename TMy, typename TOutput>
        inline typename base_range<TMy, TOutput>::output_t
            base_range<TMy, TOutput>::element_at(size_t index, const output_t& defaultValue) const
        {
            size_t i = 0;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                if (i >= index)
                {
                    return p;
                }

                ++i;
            }

            return defaultValue;
        }

        template<typename TMy, typename TOutput>
        inline std::vector<typename base_range<TMy, TOutput>::output_t>
            base_range<TMy, TOutput>::to_vector() const
        {
            std::vector<output_t> vec;

            for (const auto& p : static_cast<const TMy&>(*this))
            {
                vec.push_back(p);
            }

            return vec;
        }

    } // end namespace details

    template<typename TContainer>
    static inline details::from_container_range<TContainer> from(const TContainer* container)
    {
        return details::from_container_range<TContainer>(container);
    }

    template<typename T>
    static inline details::from_to_range<T> from_to(const T& start, const T& end, const T& step = T(1))
    {
        static_assert(
            std::is_integral<T>::value ||
            std::is_floating_point<T>::value,
            "Only integral and floating point types are supported by from_to."
            );

        return details::from_to_range<T>(start, end, step);
    }

    template<typename TGenerator>
    static inline details::generate_range<TGenerator> generate(const TGenerator& generator)
    {
        return details::generate_range<TGenerator>(generator);
    }

    template<typename T>
    static inline details::generator_return_value<T> generate_return(const T& value)
    {
        return details::generator_return_value<T>(value);
    }

    template<typename T>
    static inline details::generator_return_value<T> generate_finish()
    {
        return details::generator_return_value<T>();
    }

} // end namespace linq
