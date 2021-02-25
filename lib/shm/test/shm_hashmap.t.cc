#include "gtest/gtest.h"

extern "C" {
#include "hashmap.h"
}

const int HASHMAP_SIZE = 5;

/* Fixtures */
class HashmapTest: public ::testing::Test {
public: 
    MapValue* map_ptr;

    HashmapTest() {}

    void SetUp() {
        map_ptr = new MapValue[HASHMAP_SIZE];
    }

    void TearDown() {
        delete[] map_ptr;
    }
};

/* Tests */
TEST_F(HashmapTest, MapElementsInitializationTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        ASSERT_EQ(map_ptr[i].is_valid, false);
        ASSERT_EQ(map_ptr[i].is_deleted, false);
    }
}

TEST_F(HashmapTest, HashFunctionSanityTest) {
   ASSERT_EQ(hash("bc", HASHMAP_SIZE), hash("cB", HASHMAP_SIZE));
} 

TEST_F(HashmapTest, IntInitTest) {
    init_map(map_ptr, HASHMAP_SIZE);
    MapValue* mv = init_int_map_var("abc", 5, map_ptr, HASHMAP_SIZE);
    ASSERT_EQ(mv->is_valid, true);
    ASSERT_EQ(mv->is_deleted, false);
    ASSERT_EQ(mv->value.is_int, true);
    ASSERT_EQ(mv->value.int_value, 5);
}

TEST_F(HashmapTest, FloatInitTest) {
    init_map(map_ptr, HASHMAP_SIZE);
    MapValue* mv = init_float_map_var("abc", 2.5, map_ptr, HASHMAP_SIZE);
    ASSERT_EQ(mv->is_valid, true);
    ASSERT_EQ(mv->is_deleted, false);
    ASSERT_EQ(mv->value.is_float, true);
    ASSERT_EQ(mv->value.float_value, 2.5);
}

TEST_F(HashmapTest, BoolInitTest) {
    init_map(map_ptr, HASHMAP_SIZE);
    MapValue* mv = init_bool_map_var("abc", true, map_ptr, HASHMAP_SIZE);
    ASSERT_EQ(mv->is_valid, true);
    ASSERT_EQ(mv->is_deleted, false);
    ASSERT_EQ(mv->value.is_bool, true);
    ASSERT_EQ(mv->value.bool_value, true);
}

TEST_F(HashmapTest, CharInitTest) {
    init_map(map_ptr, HASHMAP_SIZE);
    MapValue* mv = init_char_map_var("abc", "123", map_ptr, HASHMAP_SIZE);
    ASSERT_EQ(mv->is_valid, true);
    ASSERT_EQ(mv->is_deleted, false);
    ASSERT_EQ(mv->value.is_char, true);
    ASSERT_EQ(strcmp(mv->value.char_value, "123"), 0);
}

TEST_F(HashmapTest, ReinitFailureTest) {
    init_map(map_ptr, HASHMAP_SIZE);
    MapValue* mv1 = init_int_map_var("abc", 5, map_ptr, HASHMAP_SIZE);
    MapValue* mv2 = init_int_map_var("abc", 0, map_ptr, HASHMAP_SIZE);
    ASSERT_EQ(mv1->is_valid, true);
    ASSERT_EQ(mv1->is_deleted, false);
    ASSERT_EQ(mv1->value.is_int, true);
    ASSERT_EQ(mv1->value.int_value, 5);
    ASSERT_EQ(mv2, nullptr);
}

TEST_F(HashmapTest, FullSetFailureTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv1 = init_int_map_var("a", 0, map_ptr, HASHMAP_SIZE);
    MapValue* mv2 = init_int_map_var("b", 1, map_ptr, HASHMAP_SIZE);
    MapValue* mv3 = init_int_map_var("c", 2, map_ptr, HASHMAP_SIZE);
    MapValue* mv4 = init_int_map_var("d", 3, map_ptr, HASHMAP_SIZE);
    MapValue* mv5 = init_int_map_var("e", 4, map_ptr, HASHMAP_SIZE);
    MapValue* mv6 = init_int_map_var("d", 5, map_ptr, HASHMAP_SIZE);

    ASSERT_NE(mv1, nullptr);
    ASSERT_NE(mv2, nullptr);
    ASSERT_NE(mv3, nullptr);
    ASSERT_NE(mv4, nullptr);
    ASSERT_NE(mv5, nullptr);
    ASSERT_EQ(mv6, nullptr);
}

TEST_F(HashmapTest, SimpleGetTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv1 = init_int_map_var("a", 0, map_ptr, HASHMAP_SIZE);
    MapValue* mv2 = get_map_var("a", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(mv1, mv2);
}

TEST_F(HashmapTest, MultiGetTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv1 = init_int_map_var("a", 0, map_ptr, HASHMAP_SIZE);
    MapValue* mv1g = get_map_var("a", map_ptr, HASHMAP_SIZE);
    MapValue* mv2 = init_int_map_var("b", 1, map_ptr, HASHMAP_SIZE);
    MapValue* mv2g = get_map_var("b", map_ptr, HASHMAP_SIZE);
    MapValue* mv3 = init_int_map_var("c", 2, map_ptr, HASHMAP_SIZE);
    MapValue* mv3g = get_map_var("c", map_ptr, HASHMAP_SIZE);
    MapValue* mv4 = init_int_map_var("d", 3, map_ptr, HASHMAP_SIZE);
    MapValue* mv4g = get_map_var("d", map_ptr, HASHMAP_SIZE);
    MapValue* mv5 = init_int_map_var("e", 4, map_ptr, HASHMAP_SIZE);
    MapValue* mv5g = get_map_var("e", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(mv1, mv1g);
    ASSERT_EQ(mv2, mv2g);
    ASSERT_EQ(mv3, mv3g);
    ASSERT_EQ(mv4, mv4g);
    ASSERT_EQ(mv5, mv5g);
}

TEST_F(HashmapTest, NotFoundGetTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv = get_map_var("a", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(mv, nullptr);
}

TEST_F(HashmapTest, SimpleDeleteTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv1 = init_int_map_var("a", 0, map_ptr, HASHMAP_SIZE);
    bool rc = delete_map_var("a", map_ptr, HASHMAP_SIZE);
    MapValue* mv1d = get_map_var("a", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(rc, true);
    ASSERT_EQ(mv1->is_deleted, true);
    ASSERT_EQ(mv1d, nullptr);
}

TEST_F(HashmapTest, ComplexDeleteTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    MapValue* mv1 = init_int_map_var("a", 0, map_ptr, HASHMAP_SIZE);
    MapValue* mv1g = get_map_var("a", map_ptr, HASHMAP_SIZE);
    bool mv1d = delete_map_var("a", map_ptr, HASHMAP_SIZE);

    MapValue* mv2 = init_int_map_var("b", 1, map_ptr, HASHMAP_SIZE);
    MapValue* mv2g = get_map_var("b", map_ptr, HASHMAP_SIZE);
    bool mv2d = delete_map_var("b", map_ptr, HASHMAP_SIZE);

    MapValue* mv3 = init_int_map_var("c", 2, map_ptr, HASHMAP_SIZE);
    MapValue* mv3g = get_map_var("c", map_ptr, HASHMAP_SIZE);

    MapValue* mv4 = init_int_map_var("d", 3, map_ptr, HASHMAP_SIZE);
    MapValue* mv4g = get_map_var("d", map_ptr, HASHMAP_SIZE);

    MapValue* mv5 = init_int_map_var("e", 4, map_ptr, HASHMAP_SIZE);
    MapValue* mv5g = get_map_var("e", map_ptr, HASHMAP_SIZE);

    mv2 = init_int_map_var("b", 1, map_ptr, HASHMAP_SIZE);
    mv2g = get_map_var("b", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(mv2, mv2g);
    ASSERT_EQ(mv3, mv3g);
    ASSERT_EQ(mv4, mv4g);
    ASSERT_EQ(mv5, mv5g);
}

TEST_F(HashmapTest, NotFoundDeleteTest) {
    init_map(map_ptr, HASHMAP_SIZE);

    bool rc = delete_map_var("a", map_ptr, HASHMAP_SIZE);
    MapValue* mv = get_map_var("a", map_ptr, HASHMAP_SIZE);

    ASSERT_EQ(rc, false);
    ASSERT_EQ(mv, nullptr);
}
