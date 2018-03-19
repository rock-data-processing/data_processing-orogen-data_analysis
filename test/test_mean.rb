require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

def gaussian(mean, stddev, rand_nr)
  theta = 2 * Math::PI * rand_nr
  rho = Math.sqrt(-2 * Math.log(1 - rand_nr))
  scale = stddev * rho
  x = mean + scale * Math.cos(theta)
  return x
end

Orocos.run "data_analysis::MeanTask" => "mean" do
    task = Orocos::TaskContext.get "mean"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer_rbs = task.rbs.writer
    input_rbs = Types.base.samples.RigidBodyState.new
    reader_rbs_mean    = task.mean_rbs.reader
    reader_rbs_std_dev = task.std_dev_rbs.reader

    writer_joints = task.joints.writer
    input_joints = Types.base.samples.Joints.new
    input_joints.elements = [Types.base.JointState.new]*2
    reader_joints_mean = task.mean_joints.reader
    reader_joints_std_dev = task.std_dev_joints.reader

    mean_rbs = [0.0,1.0]
    std_dev_rbs = [0.1,0.2]

    mean_joints = [2.0,3.0]
    std_dev_joints = [0.3,0.4]
    while true
        rand_nr = Random.rand
        input_rbs.position = Types.base.Vector3d.new(gaussian(mean_rbs[0], std_dev_rbs[0], rand_nr), gaussian(mean_rbs[1], std_dev_rbs[1], rand_nr))
        input_joints.elements[0].position = gaussian(mean_joints[0], std_dev_joints[0], rand_nr)
        input_joints.elements[1].position = gaussian(mean_joints[1], std_dev_joints[1], rand_nr)

        input_rbs.time = Types.base.Time.now
        writer_rbs.write input_rbs
        input_joints.time = Types.base.Time.now
        writer_joints.write input_joints

        sleep 0.1
        sample_rbs_mean = reader_rbs_mean.read
        sample_rbs_std_dev = reader_rbs_std_dev.read

        if sample_rbs_mean && sample_rbs_std_dev
            puts "RBS Port:"
            puts "Input data:       " + input_rbs.position.to_a.to_s
            puts "Expected mean:    " + mean_rbs.to_s
            puts "Mean:             " + sample_rbs_mean.to_a.to_s
            puts "Expected std dev: " + std_dev_rbs.to_s
            puts "Std dev:          " + sample_rbs_std_dev.to_a.to_s
            puts
        end

        sample_joints_mean = reader_joints_mean.read
        sample_joints_std_dev = reader_joints_std_dev.read

        if sample_joints_mean && sample_joints_std_dev
            puts "Joints Port:"
            puts "Input data:       [" + input_joints.elements[0].position.to_s + " " + input_joints.elements[1].position.to_s + "]"
            puts "Expected mean:    " + mean_joints.to_s
            puts "Mean:             " + sample_joints_mean.to_a.to_s
            puts "Expected std dev: " + std_dev_joints.to_s
            puts "Std dev:          " + sample_joints_std_dev.to_a.to_s
            puts "................................."
        end
    end
end
