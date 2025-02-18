# Changelog

<!-- ### Added -->
<!-- ### Changed -->
<!-- - **Breaking:** bla bla (`15d5a9e`) -->
<!-- ### Deprecated -->
<!-- ### Removed -->
<!-- ### Fixed -->


## [Unreleased]

### Added

- Support `nvcc` compiler.
- Add `recursion_result::f<xs...>` and `next_recursion::f<xs...>` to specify a sequence of values for the next iteration or final iteration of `recursively` and `recursively_as_much_as_possible` (previously `recurse` and `infinite_recurse`).
- Add many other algorithms.


### Changed

- **Breaking:** `FC` parameter of `find<x, TC, FC>` / `find_if<Pred, TC, FC>` now takes the input sequence rather than an empty sequence. As `FC` is initialized with `clear<TC>`, only calls that pass this parameter are affected.
- **Breaking:** Change `min<Cmp, C>::f<xs...>` to `min<C>::f<x,y>`. Old behavior is named `min_element`. Idem with `max` / `max_element`.
- **Breaking:** Change `emp::min`, `emp::max`, `emp::abs` and `emp::clamp`: no longer takes a list of parameters, but the parameters directly (`emp::abs<list<x>>` -> `emp::abs<x>`).
- Move `algorithm/indices.hpp` to `list/indices.hpp`.
- Move `algorithm/compare_with.hpp` to `functional/compare_with.hpp`.
- Move `functional/is_invocable.hpp` in `functional/try.hpp`.
- Move `abs`, `clamp` and `pow` from `number/operators.hpp` to `number/math.hpp`.
- rename `JLN_MP_ENABLE_DEBUG` to `JLN_MP_DEBUG`.
- Rename `int_` and `uint_` to `int_t` and `uint_t` respectively.
- Rename `lift*_t` to `cfl*`, `lift*` to `cfe*` and `functional/lift.hpp` to `functional/continuation.hpp`.
- Rename `lift_c` and `lift_c_t` to `cfe_v_c` and `cfl_v_c`.
- Rename `adjacent_remove`/`adjacent_remove_if` to `remove_adjacent`/`adjacent_remove_if` and `algorithm/adjacent_remove.hpp` to `algorithm/remove_adjacent.hpp`.
- Rename `cartesian` to `product` and `algorithm/cartesian.hpp` to `algorithm/product.hpp`.
- Rename `fold_left` to `fold` and `algorithm/fold_left.hpp` to `algorithm/fold.hpp`.
- Rename `group_n` to `batched` and `algorithm/group_n.hpp` to `algorithm/batched.hpp`.
- Rename `drop` to `drop_front` and `list/drop.hpp` to `list/drop_front.hpp`.
- Rename `take` to `take_front` and `list/take.hpp` to `list/take_front.hpp`.
- Rename `insert_range` to `insert_sequence` and `list/insert_range.hpp` to `list/insert_sequence.hpp`.
- Rename `same_as` to `is` and `utility/same_as.hpp` to `utility/is.hpp`.
- Rename `id_of_v` to `emp::id_of_v`.
- Rename `id_of_t` to `emp::id_of`.
- Rename `next_id()` to `emp::next_id_v<>`.
- Rename `next_random()` to `emp::random_of_v<>`.
- Rename `on` to `partial_transform0` and `functional/on.hpp` to `functional/partial_transform.hpp`.
- Rename `capture` to `capture_front` and moved from `functional/capture.hpp` to `functional/capture_front.hpp`.
- Rename `reverse_capture` to `capture_back` and moved from `functional/capture.hpp` to `functional/capture_back.hpp`.
- Rename `bind` to `bind_front` and moved from `functional/bind.hpp` to `functional/bind_front.hpp`.
- Rename `reverse_bind` to `bind_back` and moved from `functional/bind.hpp` to `functional/bind_back.hpp`.
- Rename `bind1st` to `transform_first` and moved from `functional/bind.hpp` to `algorithm/transform_first.hpp`.
- Rename `bind2nd` to `transform_second` and moved from `functional/bind.hpp` to `algorithm/transform_second.hpp`.
- Rename `functional/recurse.hpp` to `functional/recursively.hpp`.
- Rename `stop_iteration` to `stop_recursion`.
- Rename `recurse` to `recursively`.
- Rename `infinite_recurse` to `recursively_as_much_as_possible`.
- Replace `adjacent_difference<C>` with `pairwise_fold<sub<>, C>`.


### Removed

- Remove `recurse_fix` and `infinite_recurse_fix`.
- Remove `min0`, `max0`, `pow0` and `pow1`.
- Remove `dispatch_t`, `indirect_call_t`, `unary_compose_call_t`, `binary_compose_call_t` and `ternary_compose_call_t`.
- Remove `tagged_id_of`, `tagged_id_of_v`, `tagged_id_of_t` and `id_of`


## [1.0.0] - 2021-01-17

_First release._


[unreleased]: https://github.com/jonathanpoelen/jln.mp/compare/v2.0.0...HEAD
[1.1.1]: https://github.com/jonathanpoelen/jln.mp/compare/v1.0.0...v2.0.0
