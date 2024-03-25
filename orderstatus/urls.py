from django.urls import path
from . import views

urlpatterns = [
  path('orderstatus',views.orderstatus,name='orderstatus'),
]