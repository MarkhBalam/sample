from django.urls import path
from . import views

urlpatterns = [
    path('home/', views.home, name='home'),
#     path('add_product/', views.add_product, name='add_product'),
#     path('order_status/', views.order_status, name='order_status'),
#     path('account/', views.account, name='account'),
#     path('help/', views.help, name='help'),
    # other paths...
]
