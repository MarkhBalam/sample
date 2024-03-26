from django.urls import path
from . import views

urlpatterns = [
    path('',views.homepage, name="homepage"),
    path('addproduct',views.addproduct,name="addproduct"),
    path('', views.index, name='index'),
]
