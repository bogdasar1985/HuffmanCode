#include <check.h>
#include "../src/huffman.h"
// Написать тесты для добавления ноды
START_TEST(init_priority_queue_test)
{
    struct priority_queue *pq = NULL;
	ck_assert_int_eq(0, pq_init(&pq, 0));
	ck_assert_int_eq(pq->size, 0);
	ck_assert_int_eq(pq->capacity, 0);
}
END_TEST

START_TEST(init2_priority_queue_test)
{
    struct priority_queue *pq = NULL;
	pq_init(&pq, 1);
	ck_assert_int_eq(pq->size, 0);
	ck_assert_int_eq(pq->capacity, 1);
}
END_TEST

START_TEST(add_priority_queue_test)
{
	struct priority_queue *pq = NULL;
	pq_init(&pq, 5);
	pq_insert_element(pq, 'a', 1, NULL);
	ck_assert_int_eq(pq->size, 1);
	pq_insert_element(pq, 'a', 1, NULL);
	ck_assert_int_eq(pq->size, 1);
	pq_insert_element(pq, 'b', 1, NULL);
	ck_assert_int_eq(pq->size, 2);
}
END_TEST

START_TEST(extract_min_test)
{
	struct priority_queue *pq = NULL;
	pq_init(&pq, 5);
	pq_insert_element(pq, 'a', 1, NULL);
	pq_insert_element(pq, 'b', 1, NULL);
	pq_insert_element(pq, 'b', 1, NULL);
	ck_assert_int_eq('a', pq_extract_min(pq)->symbol);
	ck_assert_int_eq('b', pq_extract_min(pq)->symbol);
	ck_assert_int_eq(0, pq->size);
}
END_TEST

START_TEST(node_swap_test)
{
	struct pq_node *pq = malloc(sizeof(struct pq_node));
	struct pq_node *pq2 = malloc(sizeof(struct pq_node));
	pq->symbol = 'a';
	pq2->symbol = 'b';
	node_swap(&pq, &pq2);
	ck_assert_int_eq(pq->symbol, 'b');
	ck_assert_int_eq(pq2->symbol, 'a');
}
END_TEST

START_TEST(find_test)
{
	struct priority_queue *pq = NULL;
	pq_init(&pq, 5);
	pq_insert_element(pq, 'a', 1, NULL);
	pq_insert_element(pq, 'b', 1, NULL);
	pq_insert_element(pq, 'b', 1, NULL);
	ck_assert_int_ge(pq_find(pq, 'a'), 0);
	ck_assert_int_ge(pq_find(pq, 'b'), 0);
	ck_assert_int_eq(pq_find(pq, 'f'), -1);
}
END_TEST

START_TEST(build_tree)
{
	struct priority_queue *pq = NULL;
	pq_init(&pq, 1);
    pq_insert_element(pq, 'a', 51, NULL);
    pq_insert_element(pq, 'b', 3, NULL);
    pq_insert_element(pq, 'c', 6, NULL);
    pq_insert_element(pq, 'd', 12, NULL);
	pq_insert_element(pq, 'e', 21, NULL);
	pq_insert_element(pq, 'f', 32, NULL);
	pq_insert_element(pq, 'g', 44, NULL);
	while (pq->size > 1)
    {
        struct pq_node *tmp1 = pq_extract_min(pq);
		struct pq_node *tmp2 = pq_extract_min(pq);
		struct pq_node *tmp3 = tr_build(tmp1, tmp2);

		ck_assert_ptr_eq(tmp3->left->parent, tmp3);
		ck_assert_ptr_eq(tmp3->right->parent, tmp3);

		pq_insert_element(pq, -1, -1, tmp3);
    }
}
END_TEST

START_TEST(test_pq_fill_from_pq)
{
	struct priority_queue *pq1 = NULL;
	struct priority_queue *pq2 = NULL;
	pq_init(&pq1, 1);
    pq_insert_element(pq1, 'a', 51, NULL);
    pq_insert_element(pq1, 'b', 3, NULL);
    pq_insert_element(pq1, 'c', 6, NULL);
    pq_insert_element(pq1, 'd', 12, NULL);

	pq_init(&pq2, pq1->capacity);
	pq_fill_from_pq(&pq2, pq1);

	ck_assert_int_eq(pq1->size, pq2->size);
	ck_assert_int_eq(pq1->capacity, pq2->capacity);

	for(size_t i = 0; i < pq1->size; ++i)
	{
		ck_assert_int_eq(pq1->heap_on_array[i]->frequency, pq2->heap_on_array[i]->frequency);
		ck_assert_int_eq(pq1->heap_on_array[i]->symbol, pq2->heap_on_array[i]->symbol);
	}
}
END_TEST

int main(void)
{
	Suite *suite = suite_create("Core");
	TCase *test_case = tcase_create("Core");
	SRunner *suite_runner = srunner_create(suite);
	int nf;

	suite_add_tcase(suite, test_case);
	tcase_add_test(test_case, init_priority_queue_test);
	tcase_add_test(test_case, init2_priority_queue_test);
	tcase_add_test(test_case, add_priority_queue_test);
	tcase_add_test(test_case, extract_min_test);
	tcase_add_test(test_case, node_swap_test);
	tcase_add_test(test_case, find_test);
	tcase_add_test(test_case, build_tree);
	tcase_add_test(test_case, test_pq_fill_from_pq);

	srunner_run_all(suite_runner, CK_ENV);
	nf = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);

	return nf == 0 ? 0 : 1;
}
