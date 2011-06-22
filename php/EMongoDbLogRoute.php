<?php
/**
 * Auther aoyagikouhei
 * 2011/06/23 ver 1.0
 *
 * Install
 * Extract the release file under protected/extensions
 * 
 * In config/main.php:
  'log'=>array(
      'class'=>'CLogRouter',
      'routes'=>array(
        array(
          'class'=>'ext.EMongoDbLogRoute',
          'levels'=>'trace, info, error, warning',
          'categories' => 'system.*',
        ),
      ),
    ),
 *
 * options
 * connectionString : host:port             : defalut localhost:27017
 * dbName           : database name         : default test
 * collectionName   : collaction name       : default yiilog
 * message          : message column name   : default message
 * level            : level column name     : default level
 * category         : category column name  : default category
 * timestamp        : timestamp column name : default timestamp
 * timestampType    : float or date         : default float
 *
 * example
   'log'=>array(
      'class'=>'CLogRouter',
      'routes'=>array(
        array(
          'class'=>'ext.EMongoDbLogRoute',
          'levels'=>'trace, info, error, warning',
          'categories' => 'system.*',
          'connectionString' => 'localhost:27017',
          'dbName' => 'test',
          'collectionName' => 'yiilog',
          'message' => 'message',
          'level' => 'level',
          'category' => 'category',
          'timestamp' => 'timestamp',
          'timestampType' => 'float',
        ),
      ),
    ),
 *
 */
class EMongoDbLogRoute extends CLogRoute
{
  /**
   * @var string Mongo Db host + port
   */
  public $connectionString="localhost:27017";

  /**
   * @var string Mongo Db Name
   */
  public $dbName="test";
  
  /**
   * @var string Collection name
   */
  public $collectionName="yiilog";

  /**
   * @var string message column name
   */
  public $message="message";

  /**
   * @var string level column name
   */
  public $level="level";

  /**
   * @var string category column name
   */
  public $category="category";

  /**
   * @var string timestamp column name
   */
  public $timestamp="timestamp";

  /**
   * @var string timestamp type name float or date
   */
  public $timestampType="float";

  /**
  /**
   * @var Mongo mongo Db collection
   */
  private $collection;
   
  /**
   * Initializes the route.
   * This method is invoked after the route is created by the route manager.
   */
  public function init()
  {
    parent::init();
    $connection = new Mongo($this->connectionString);
    $dbName = $this->dbName;
    $collectionName = $this->collectionName;
    $this->collection = $connection->$dbName->$collectionName;
  }

  /**
   * Saves log messages into mongodb.
   * @param array list of log messages
   */
  protected function processLogs($logs)
  {
    foreach($logs as $log) {
      $this->collection->insert(array(
        $this->message => $log[0]
        ,$this->level => $log[1]
        ,$this->category => $log[2]
        ,$this->timestamp => 
          'date' === $this->timestampType ? new MongoDate(round($log[3])) : $log[3]
      ));
    }
  }

}
