#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/linkage.h>
#include <linux/highmem.h>
#include <linux/gfp.h>


asmlinkage unsigned long sys_vtop(unsigned long *initial, int len_vir, unsigned long *result) {
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	unsigned long *v_addr = kmalloc(len_vir * sizeof(unsigned long),GFP_KERNEL);
	unsigned long *p_addr = kmalloc(len_vir * sizeof(unsigned long),GFP_KERNEL);
	copy_from_user(v_addr, initial, len_vir * sizeof(unsigned long));
	printk("cpaddr[0]:%p\n", v_addr[0]);
	printk("cpaddr[1]:%p\n", v_addr[1]);
	printk("cpaddr[2]:%p\n", v_addr[2]);
	printk("cpaddr[3]:%p\n", v_addr[3]);
	printk("cpaddr[4]:%p\n", v_addr[4]);
	printk("cpaddr[5]:%p\n", v_addr[5]);

	struct page *page;
	int i=0;
	for(; i<len_vir;i++){

		pgd = pgd_offset(current->mm, v_addr[i]);
		printk("pgd_val = 0x%lx\n", pgd_val(*pgd));
		printk("pgd_index = %lu\n", pgd_index(v_addr[i]));
		if (pgd_none(*pgd)) {
			printk("not mapped in pgd\n");
			return -1;
		}

		pud = pud_offset(pgd, v_addr[i]);
		printk("pud_val = 0x%lx\n", pud_val(*pud));
		if (pud_none(*pud)) {
			printk("not mapped in pud\n");
			return -1;
		}

		pmd = pmd_offset(pud, v_addr[i]);
		printk("pmd_val = 0x%lx\n", pmd_val(*pmd));
		printk("pmd_index = %lu\n", pmd_index(v_addr[i]));
		if (pmd_none(*pmd)) {
			printk("not mapped in pmd\n");
			return -1;
		}

		pte = pte_offset_map(pmd, v_addr[i]);

		if (pte_none(*pte)) {
			printk("not mapped in pte\n");
		}
		page=pte_page(*pte);
		pte_unmap(pte);
		p_addr[i]=(page_to_phys(page) & PAGE_MASK) | (v_addr[i] & ~PAGE_MASK);
		printk("p_addr:%p\n", p_addr[i]);
	}
	copy_to_user(result, p_addr, len_vir * sizeof(unsigned long));

	return 0;

}
