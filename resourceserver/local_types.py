import mysql.connector

# Generic SQL Adapter Model
class Model(object):
  fields = ['id']
  table_name = ''

  def __init__(self, info):
    for idx, value in enumerate(info):
      setattr(self, self.fields[idx], value)

  @classmethod
  def find(cls, ids):
    sql = """SELECT %s FROM %s WHERE id IN (%s);""" % \
             (','.join(cls.fields), cls.table_name, ','.join(str(i) for i in ids))
    return sql

  @classmethod
  def all(cls):
    return """SELECT %s FROM %s;""" % (','.join(cls.fields), cls.table_name)

  @classmethod
  def create(cls, values):
    fields = []
    vals = []

    for f, v in values.iteritems():
      fields.append(str(f))
      vals.append(str(v))

    return """INSERT INTO %s (%s) VALUES (\"%s\");""" % (cls.table_name, ','.join(fields), '","'.join(vals))

  @classmethod
  def destroy(cls, ids):
    return """DELETE FROM %s WHERE id IN (%s);""" % (cls.table_name, ','.join(str(i) for i in ids))



#######
### MODELS
#######

class Resource(Model):
  table_name = 'resources'
  fields = ['id', 'file_name', 'resource_type']

class ResourceType(Model):
  table_name = 'resource_types'
  fields = ['id', 'name']


#######
#######

# Class for managing the connection to the database
class Database(object):
  def __init__(self, config):
    self.config = config
    self.connection = mysql.connector.connect(**config)

  def close(self):
    self.connection.close()


  def get(self, klass, ids):
    sql = klass.find(ids)
    return self.query(sql, klass)



  def all(self, klass):
    sql = klass.all()
    return self.query(sql, klass)


  def create(self, klass, **values):
    sql = klass.create(values)
    self.query(sql, commit=True)
    return None # INSERT queries don't return any data


  def edit(self, klass, id, **values):
    # TODO: Implement editing
    pass


  def destroy(self, klass, id):
    sql = klass.destroy(id)
    self.query(sql, klass, commit=True)
    return None # DELETE queries don't return any data


  # If `klass` is specified, returns a list of objects of that type.
  # Otherwise, returns the cursor to the database result.
  def query(self, sql, klass=None, multi=False, commit=False):
    # Ensure a connection has been established and
    try:
      cursor = self.connection.cursor()
      cursor.execute(sql, multi)
    except Exception:
      self.connection = mysql.connector.connect(**self.config)
      cursor = self.connection.cursor()
      cursor.execute(sql, multi)

    print "Executing SQL:", sql

    if commit: self.connection.commit()

    if commit:
      return None
    elif klass:
      return [klass(ent) for ent in cursor.fetchall()]
    else:
      return cursor
