

#include <config.h>
#include <malloc.h>
#include <printk.h>

extern unsigned int _end;

void test_malloc() {
	int fails = 0;
	unsigned int tmp_end;
	unsigned int *tmp_ptr;
	printk("Test: malloc ");

	if (!(_end > 0x40000000 && _end < 0x50000000)) {
		fails++;
		printk("\r\n_end is not where it is expected to be");
	}

	tmp_end = _end;
	tmp_ptr = malloc(sizeof(unsigned int));
	if (((unsigned int)tmp_ptr) != tmp_end) {
		fails++;
		printk("\r\nmalloc is not allocating at _end (%d) getting (%d)",
			_end, tmp_ptr);
	}

	_end = tmp_end; 	/* reset _end, instead of freeing */
	tmp_ptr = malloc(sizeof(unsigned int)*20);
	if (_end != (tmp_end + (sizeof(unsigned int)*20))) {
		fails++;
		printk("\r\nmalloc does not allocate arrays correctly");
	}

	_end = tmp_end;
	tmp_ptr = malloc_aligned(sizeof(unsigned int)*20, 0x1000);
	if (((unsigned int)tmp_ptr) % 0x1000) {
		fails++;
		printk("\r\nmalloc_aligned does not allocate in alignment correctly");
	}
	_end = tmp_end;

	if (fails > 0)
		printk(" [FAIL]\r\n");
	else
		printk(" [PASS]\r\n");
}

