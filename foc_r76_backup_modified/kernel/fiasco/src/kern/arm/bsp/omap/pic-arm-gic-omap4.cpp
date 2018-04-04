INTERFACE [arm && pic_gic && (pf_omap4 || pf_omap5)]:

#include "initcalls.h"
#include "gic.h"

// ------------------------------------------------------------------------
IMPLEMENTATION [arm && pic_gic && (pf_omap4 || pf_omap5)]:

#include "irq_mgr_multi_chip.h"
#include "kmem.h"

PUBLIC static FIASCO_INIT
void
Pic::init()
{
  typedef Irq_mgr_multi_chip<8> M;

  M *m = new Boot_object<M>(1);

  gic.construct(Kmem::mmio_remap(Mem_layout::Gic_cpu_phys_base),
                Kmem::mmio_remap(Mem_layout::Gic_dist_phys_base));
  m->add_chip(0, gic, gic->nr_irqs());

  Irq_mgr::mgr = m;
}

// ------------------------------------------------------------------------
IMPLEMENTATION [arm && mp && pic_gic && (pf_omap4 || pf_omap5)]:

PUBLIC static
void Pic::init_ap(Cpu_number, bool resume)
{
  gic->init_ap(resume);
}
