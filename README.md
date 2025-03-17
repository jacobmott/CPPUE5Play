# CPPUE5Play
Unreal 5.5/C++ refresher







## For me
The Screenshots folder and Content folder are stored in s3 bucket

Pull down from bucket
```
  #Execute this from the directory above CPPUE5UltGameDevCrs
  aws s3 cp --recursive s3://<bucket>/CPPUE5Play/Content CPPUE5Play/Content
  aws s3 cp --recursive s3://<bucket>/CPPUE5Play/Assets CPPUE5Play/Assets
  aws s3 cp --recursive s3://<bucket>/CPPUE5Play/Screenshots CPPUE5Play/Screenshots

```

Push to bucket
```
  #Execute this from the directory above CPPUE5Play
  aws s3 cp --recursive CPPUE5Play/Content s3://<bucket>/CPPUE5Play/Content
  aws s3 cp --recursive CPPUE5Play/Assets s3://<bucket>/CPPUE5Play/Assets
  aws s3 cp --recursive CPPUE5Play/Screenshots s3://<bucket>/CPPUE5Play/Screenshots

```

Or just do a sync
```
  #Execute this from the directory above CPPUE5Play
  aws s3 sync CPPUE5Play/Content s3://<bucket>/CPPUE5Play/Content --delete
  aws s3 sync CPPUE5Play/Assets s3://<bucket>/CPPUE5Play/Assets --delete
  aws s3 sync CPPUE5Play/Screenshots s3://<bucket>/CPPUE5Play/Screenshots --delete

```
