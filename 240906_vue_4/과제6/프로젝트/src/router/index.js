import { createRouter, createWebHistory } from "vue-router";

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    //-----------------사용자-----------------//
    {
      path: "/",
      name: "home",
      component: () => import("../views/order/MainView.vue"),
    },
    {
      path: "/orders",
      name: "orders",
      component: () => import("../views/order/ListView.vue"),
    },
    {
      path: "/orders/register",
      name: "order-register",
      component: () => import("../views/order/RegisterView.vue"),
    },
    {
      path: "/orders/register/:id",
      name: "order-update",
      component: () => import("../views/order/RegisterView.vue"),
    },
    {
      path: "/orders/:id",
      name: "order-detail",
      component: () => import("../views/order/DetailView.vue"),
    },
    //-----------------어드민-----------------//
    {
      path: "/admin/home",
      name: "menus-home",
      component: () => import("../views/admin-menu/MainView.vue"),
    },
    {
      path: "/admin/menus",
      name: "menus",
      component: () => import("../views/admin-menu/ListView.vue"),
    },
    {
      path: "/admin/menus/register",
      name: "menu-register",
      component: () => import("../views/admin-menu/RegisterView.vue"),
    },
    {
      path: "/admin/menus/register/:id",
      name: "menu-update",
      component: () => import("../views/admin-menu/RegisterView.vue"),
    },
    {
      path: "/admin/menus/:id",
      name: "menu-detail",
      component: () => import("../views/admin-menu/DetailView.vue"),
    },
  ],
});

export default router;
