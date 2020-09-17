// Упорядочить тесты.
// Создать fixture
// По-нормальному всё сделать, короче.
#include <check.h>
#include "../src/huffman.h"
START_TEST(_heap)
{
    struct heap *heap = NULL;
    struct tree *tree = NULL;
    
    init_heap(&heap);
    
    ck_assert_int_eq(heap->size, 0);
    ck_assert_int_eq(heap->capacity, 1);

    for(size_t i = 0; i < 3; ++i)
    {
        insert(&heap, 'a');
    }
    
    ck_assert_int_eq(heap->size, 1);
    
    for(size_t i = 0; i < 2; ++i)
    {
        insert(&heap, 'b');
    }
    
    ck_assert_int_eq(heap->size, 2);

    init_tree(&tree, (heap->size) + (heap->size) + 1);
    fill_tree(&tree, &heap);

    ck_assert_int_eq(tree->size, 3);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");       // Что это?
	TCase *tc1_1 = tcase_create("Core");    // Что это?
	SRunner *sr = srunner_create(s1);       // Что это?
	int nf;

	suite_add_tcase(s1, tc1_1);
	tcase_add_test(tc1_1, _heap);

	srunner_run_all(sr, CK_ENV);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);

	return nf == 0 ? 0 : 1;
}