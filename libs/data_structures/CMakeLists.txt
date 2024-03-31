add_library(data_structures
        bitset/bitset.c
        vector/vector.c
        vectorVoid/vectorVoid.c
        matrix/matrix.c
        )

taget_link_libraries(data_structures algorithms)