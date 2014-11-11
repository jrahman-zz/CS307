import mysql.connector

# Generic SQL Adapter Model
class Model(object):
  fields = ['id']
  table_name = ''

  def __init__(self, info):
    for idx, value in enumerate(info):
      setattr(self, self.fields[idx], value)

  @classmethod
  def sql_for(cls, ids):
    sql = """SELECT %s FROM %s WHERE id IN (%s)""" % \
             (','.join(cls.fields), cls.table_name, ','.join(str(i) for i in ids))
    return sql



#######
### MODELS
#######

class Resource(Model):
  table_name = 'resources'
  fields = ['file_name', 'mime_type', 'resource_type']

class ResourceType(Model):
  table_name = 'resource_types'
  fields = ['id', 'name']


#######
#######

# Class for managing the connection to the database
class Database(object):
  def __init__(self, config):
    self.connection = mysql.connector.connect(**config)
    self.cursor = self.connection.cursor()

  def close(self):
    self.connection.close()
    self.cursor = None


  def get(self, klass, ids):
    query = klass.sql_for(ids)
    self.cursor.execute(query)
    result = self.cursor.fetchone()

    # data, mime_type, resource_type = result
    return klass(result) if result else None


  def create(self, klass, info):
    pass

  def edit(self, klass, id, info):
    pass

  def delete(self, klass, id):
    pass

  def query(self, sql):
    return cursor.execute(query)
