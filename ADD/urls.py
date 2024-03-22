
from django.urls import path
from . import views

urlpatterns = [
    path('order/', views.order, name="order" ),
    path('add/', views.add, name="add")
]