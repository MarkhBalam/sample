

# Create your models here.


from django.db import models

class Order(models.Model):
    # Define fields for the Order model
    price = models.DecimalField(max_digits=10, decimal_places=2)
    date = models.DateField()
    description = models.CharField(max_length=255)

    def __str__(self):
        return self.description  # Or any other field you want to represent this model by

class OrderStatus(models.Model):
    # Define choices for order statuses
    STATUS_CHOICES = (
        ('new', 'New Order'),
        ('pending', 'Pending Order'),
        ('cleared', 'Cleared Order'),
    )

    # Define fields for the OrderStatus model
    order = models.ForeignKey(Order, on_delete=models.CASCADE)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES)

    def __str__(self):
        return f"{self.order.description} - {self.get_status_display()}"



class YourModel(models.Model):
    # Define fields for YourModel
    field1 = models.CharField(max_length=100)
    field2 = models.IntegerField()

    def __str__(self):
        return self.field1
