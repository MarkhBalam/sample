
from django.urls import path
from . import views

urlpatterns = [
    path('orderstatus/', views.orderstatus, name='orderstatus'),
    path('orderstatus/orders/', views.order_list, name='order_list'),
    path('orderstatus/orders/<int:order_id>/', views.order_detail, name='order_detail'),
]
