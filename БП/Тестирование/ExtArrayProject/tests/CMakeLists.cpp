#include <gtest/gtest.h>
#include "ExtArray.h"

TEST(ExtArrayTest, EmptyArrayTests) {
    ExtArray<int> emptyIntArray(0);
    EXPECT_EQ(emptyIntArray.size(), 0);
    EXPECT_EQ(emptyIntArray.mean(), 0);
    EXPECT_EQ(emptyIntArray.median(), 0);

    auto modeResult = emptyIntArray.mode();
    EXPECT_EQ(modeResult.first, 0);
    EXPECT_EQ(modeResult.second, 0);

    ExtArray<double> emptyDoubleArray({});
    EXPECT_EQ(emptyDoubleArray.size(), 0);
    EXPECT_EQ(emptyDoubleArray.mean(), 0);
    EXPECT_EQ(emptyDoubleArray.median(), 0);

    auto modeResultDouble = emptyDoubleArray.mode();
    EXPECT_EQ(modeResultDouble.first, 0.0);
    EXPECT_EQ(modeResultDouble.second, 0);
}

TEST(ExtArrayTest, MeanRangeTests) {
    ExtArray<int> array({ 1, 2, 3, 4, 5 });

    EXPECT_DOUBLE_EQ(array.mean(0, 5), 3.0);
    EXPECT_DOUBLE_EQ(array.mean(1, 4), 3.0);
    EXPECT_DOUBLE_EQ(array.mean(2, 5), 4.0);

    EXPECT_DOUBLE_EQ(array.mean(0, 1), 1.0);
    EXPECT_DOUBLE_EQ(array.mean(4, 5), 5.0);

    EXPECT_THROW(array.mean(3, 3), std::invalid_argument);
    EXPECT_THROW(array.mean(4, 2), std::invalid_argument);
    EXPECT_THROW(array.mean(-1, 3), std::out_of_range);
    EXPECT_THROW(array.mean(2, 10), std::out_of_range);
}

TEST(ExtArrayTest, CheckSumTests) {
    ExtArray<bool> boolArray1({ true, false, true, true });
    EXPECT_EQ(boolArray1.checkSum(), 3);

    ExtArray<bool> boolArray2({ false, false, false });
    EXPECT_EQ(boolArray2.checkSum(), 0);

    ExtArray<int> intArray1({ 1, 0, 1, 1, 0 });
    EXPECT_EQ(intArray1.checkSum(), 3);

    ExtArray<int> intArray2({ 0, 0, 0 });
    EXPECT_EQ(intArray2.checkSum(), 0);

    ExtArray<int> invalidIntArray({ 1, 0, 2, 1 });
    EXPECT_THROW(invalidIntArray.checkSum(), std::logic_error);

    ExtArray<double> doubleArray({ 1.1, 2.2, 3.3 });
    EXPECT_THROW(doubleArray.checkSum(), std::bad_typeid);

    ExtArray<std::string> stringArray({ "a", "b", "c" });
    EXPECT_THROW(stringArray.checkSum(), std::bad_typeid);
}